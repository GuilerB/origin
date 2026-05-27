#include "searcherwindow.h"
#include "ui_searcherwindow.h"
#include "tokenizer.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// WordListLoader работает в отдельном потоке

WordListLoader::WordListLoader(QObject *parent) : QObject(parent)
{
// Уникальное имя соединения для каждого экземпляра
    m_connectionName = QString("thread_connection_%1")
                           .arg(reinterpret_cast<quintptr>(this));
}

WordListLoader::~WordListLoader()
{
    if (m_threadDb.isOpen()) {
        m_threadDb.close();
    }

// Сначала объект обнуляется, потом удаляется из пула
    QString connName = m_connectionName;
    m_threadDb = QSqlDatabase();

    QSqlDatabase::removeDatabase(connName);
}

QVector<QPair<QString, int>> WordListLoader::loadWordList()
{
    m_threadDb = QSqlDatabase::addDatabase("QPSQL", m_connectionName);
    m_threadDb.setHostName(DB::instance().databaseHost);
    m_threadDb.setPort(DB::instance().databasePort);
    m_threadDb.setDatabaseName(DB::instance().databaseName);
    m_threadDb.setUserName(DB::instance().databaseUser);
    m_threadDb.setPassword(DB::instance().databasePassword);

    if (!m_threadDb.open()) {
        emit error("Не удалось подключиться к БД из рабочего потока: "
                   + m_threadDb.lastError().text());
        return {};
    }

    QVector<QPair<QString, int>> result = DB::loadWordsWithConnection(m_threadDb);

    m_threadDb.close();
    return result;
}

// SearcherWindow

SearcherWindow::SearcherWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SearcherWindow)
{
    ui->setupUi(this);

    ui->wordsTable->setColumnCount(2);
    ui->wordsTable->setHorizontalHeaderLabels({"Слово", "Частота"});
    ui->wordsTable->horizontalHeader()->setStretchLastSection(true);
    ui->wordsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->wordsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->relevanceTable->setColumnCount(2);
    ui->relevanceTable->setHorizontalHeaderLabels({"Документ", "Релевантность"});
    ui->relevanceTable->horizontalHeader()->setStretchLastSection(true);
    ui->relevanceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->relevanceTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->showRelevanceButton->setEnabled(false);

    connect(ui->searchButton, &QPushButton::clicked, this, &SearcherWindow::onSearchClicked);
    connect(ui->searchLineEdit, &QLineEdit::returnPressed, this, &SearcherWindow::onSearchClicked);
    connect(ui->showRelevanceButton, &QPushButton::clicked, this, &SearcherWindow::onShowRelevanceClicked);

    loadWordList();
}

SearcherWindow::~SearcherWindow()
{
    delete ui;
}

void SearcherWindow::loadWordList()
{
    QThread *thread = new QThread(this);
    WordListLoader *loader = new WordListLoader();
    loader->moveToThread(thread);

    connect(loader, &WordListLoader::finished, this, &SearcherWindow::onWordListLoaded);
    connect(loader, &WordListLoader::error, this, &SearcherWindow::onWordListError);
    connect(loader, &WordListLoader::finished, loader, &QObject::deleteLater);
    connect(loader, &WordListLoader::error, loader, &QObject::deleteLater);
    connect(loader, &WordListLoader::finished, thread, &QThread::quit);
    connect(loader, &WordListLoader::error, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

// Вызов только после гарантированного старта потока
    connect(thread, &QThread::started, loader, [loader]() {
        QVector<QPair<QString, int>> wordList = loader->loadWordList();
        if (!wordList.isEmpty()) {
            emit loader->finished(wordList);
        }
        // Если список пуст — ошибка уже отправлена внутри loadWordList()
    });

    thread->start();
}

void SearcherWindow::onWordListLoaded(const QVector<QPair<QString, int>> &wordList)
{
    ui->wordsTable->setRowCount(wordList.size());
    for (int i = 0; i < wordList.size(); ++i) {
        ui->wordsTable->setItem(i, 0, new QTableWidgetItem(wordList[i].first));
        ui->wordsTable->setItem(i, 1, new QTableWidgetItem(QString::number(wordList[i].second)));
    }
}

void SearcherWindow::onWordListError(const QString &message)
{
    qWarning() << "Word list loading error:" << message;
}

void SearcherWindow::onSearchClicked()
{
    QString query = ui->searchLineEdit->text().trimmed();
    if (query.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите поисковый запрос.");
        return;
    }

    QStringList words = parseSearchQuery(query);
    if (words.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет допустимых слов в запросе.");
        return;
    }
    if (words.size() > 4) {
        QMessageBox::warning(this, "Ошибка", "Не более 4 слов.");
        return;
    }

    m_lastSearchResults = DB::instance().search(words, 10);
    displaySearchResults(m_lastSearchResults);
    ui->showRelevanceButton->setEnabled(!m_lastSearchResults.isEmpty());
}

void SearcherWindow::onShowRelevanceClicked()
{
    ui->relevanceTable->setRowCount(m_lastSearchResults.size());
    for (int i = 0; i < m_lastSearchResults.size(); ++i) {
        QFileInfo fi(m_lastSearchResults[i].filePath);
        ui->relevanceTable->setItem(i, 0, new QTableWidgetItem(fi.fileName()));
        ui->relevanceTable->setItem(i, 1, new QTableWidgetItem(QString::number(m_lastSearchResults[i].relevance)));
    }
    ui->tabWidget->setCurrentIndex(2);
}

QStringList SearcherWindow::parseSearchQuery(const QString &query)
{
    return Tokenizer::tokenize(query);
}

void SearcherWindow::displaySearchResults(const QVector<SearchResult> &results)
{
    ui->resultsTextEdit->clear();
    if (results.isEmpty()) {
        ui->resultsTextEdit->setHtml("<p style='color:#888'>Ничего не найдено.</p>");
        return;
    }
    QString resText = "<h3>Результаты:</h3><ol>";
    for (const auto &r : results) {
        QFileInfo fi(r.filePath);
        resText += QString("<li><b>%1</b> (релевантность: %2)<br><small>%3</small></li>")
                       .arg(fi.fileName().toHtmlEscaped())
                       .arg(r.relevance)
                       .arg(r.filePath.toHtmlEscaped());
    }
    resText += "</ol>";
    ui->resultsTextEdit->setHtml(resText);
}
