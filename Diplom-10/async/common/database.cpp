#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSettings>
#include <QDebug>

DB::DB() : databasePort(5432) {}

DB::~DB()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

DB& DB::instance()
{
    static DB inst;
    return inst;
}

bool DB::openConnection(const QString &host, int port, const QString &dbName,
                        const QString &user, const QString &password)
{
    m_database = QSqlDatabase::addDatabase("QPSQL");
    m_database.setHostName(host);
    m_database.setPort(port);
    m_database.setDatabaseName(dbName);
    m_database.setUserName(user);
    m_database.setPassword(password);

    if (!m_database.open()) {
        qCritical() << "Database connection failed:" << m_database.lastError().text();
        return false;
    }

    QSqlQuery query(m_database);
    query.exec("SET client_min_messages TO WARNING");

    qDebug() << "Database connected.";
    return true;
}

bool DB::initializeFromConfig(const QString &configPath)
{
    QSettings appConfig(configPath, QSettings::IniFormat);

    appConfig.beginGroup("Database");
    databaseHost = appConfig.value("host", "localhost").toString();
    databasePort = appConfig.value("port", 5432).toInt();
    databaseName = appConfig.value("name", "search_engine").toString();
    databaseUser = appConfig.value("user", "postgres").toString();
    databasePassword = appConfig.value("password", "postgres").toString();
    appConfig.endGroup();

    if (!openConnection(databaseHost, databasePort, databaseName,
                        databaseUser, databasePassword)) {
        return false;
    }

    if (!createTables()) {
        return false;
    }

    return true;
}

QSqlDatabase& DB::connection()
{
    return m_database;
}

// Разделённые методы: запрос и чтение, вызываются в getAllWordsWithFrequency

QSqlQuery DB::executeWordsQuery()
{
    QSqlQuery query(m_database);
    query.exec(
        "SELECT w.word, SUM(wf.frequency) AS total_freq "
        "FROM words w "
        "JOIN word_frequencies wf ON w.id = wf.word_id "
        "GROUP BY w.word "
        "ORDER BY total_freq DESC"
    );
    return query;
}

QVector<QPair<QString, int>> DB::readWordsFromQuery(QSqlQuery &query)
{
    QVector<QPair<QString, int>> result;
    while (query.next()) {
        result.append({query.value(0).toString(), query.value(1).toInt()});
    }
    return result;
}

QVector<QPair<QString, int>> DB::getAllWordsWithFrequency()
{
    QSqlQuery query = executeWordsQuery();
    return readWordsFromQuery(query);
}

// Статический метод для запроса на любом из соединений
QVector<QPair<QString, int>> DB::loadWordsWithConnection(QSqlDatabase &db)
{
    QVector<QPair<QString, int>> result;
    QSqlQuery query(db);
    query.exec(
        "SELECT w.word, SUM(wf.frequency) AS total_freq "
        "FROM words w "
        "JOIN word_frequencies wf ON w.id = wf.word_id "
        "GROUP BY w.word "
        "ORDER BY total_freq DESC"
    );
    while (query.next()) {
        result.append({query.value(0).toString(), query.value(1).toInt()});
    }
    return result;
}

// Разделённые методы: запрос и чтение, вызываются в search

QSqlQuery DB::executeSearchQuery(const QStringList &words, int limit)
{
    QStringList placeholders;
    for (int i = 0; i < words.size(); ++i) {
        placeholders << QString(":word%1").arg(i);
    }

    QString sql = QString(
        "SELECT d.file_path, SUM(wf.frequency) AS relevance "
        "FROM documents d "
        "JOIN word_frequencies wf ON d.id = wf.document_id "
        "JOIN words w ON w.id = wf.word_id "
        "WHERE w.word IN (%1) "
        "GROUP BY d.id, d.file_path "
        "HAVING COUNT(DISTINCT w.word) = :word_count "
        "ORDER BY relevance DESC "
        "LIMIT :limit"
    ).arg(placeholders.join(", "));

    QSqlQuery query(m_database);
    query.prepare(sql);
    for (int i = 0; i < words.size(); ++i) {
        query.bindValue(QString(":word%1").arg(i), words[i]);
    }
    query.bindValue(":word_count", words.size());
    query.bindValue(":limit", limit);

    if (!query.exec()) {
        qWarning() << "Search query failed:" << query.lastError().text();
    }

    return query;
}

QVector<SearchResult> DB::readSearchResults(QSqlQuery &query)
{
    QVector<SearchResult> results;
    while (query.next()) {
        SearchResult sr;
        sr.filePath = query.value(0).toString();
        sr.relevance = query.value(1).toInt();
        results.append(sr);
    }
    return results;
}

QVector<SearchResult> DB::search(const QStringList &words, int limit)
{
    QSqlQuery query = executeSearchQuery(words, limit);
    return readSearchResults(query);
}

// Таблицы

bool DB::createTables()
{
    QSqlQuery query(m_database);

    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS documents ("
        "  id SERIAL PRIMARY KEY,"
        "  file_path TEXT NOT NULL UNIQUE"
        ")")) {
        qCritical() << "Create documents table failed:" << query.lastError().text();
        return false;
    }

    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS words ("
        "  id SERIAL PRIMARY KEY,"
        "  word TEXT NOT NULL UNIQUE"
        ")")) {
        qCritical() << "Create words table failed:" << query.lastError().text();
        return false;
    }

    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS word_frequencies ("
        "  document_id INTEGER NOT NULL REFERENCES documents(id) ON DELETE CASCADE,"
        "  word_id INTEGER NOT NULL REFERENCES words(id) ON DELETE CASCADE,"
        "  frequency INTEGER NOT NULL DEFAULT 1,"
        "  PRIMARY KEY (document_id, word_id)"
        ")")) {
        qCritical() << "Create word_frequencies table failed:" << query.lastError().text();
        return false;
    }

    query.exec("CREATE INDEX IF NOT EXISTS idx_words_word ON words(word)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_wf_word_id ON word_frequencies(word_id)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_wf_document_id ON word_frequencies(document_id)");

    return true;
}

void DB::clearTables()
{
    QSqlQuery query(m_database);
    query.exec("DELETE FROM word_frequencies");
    query.exec("DELETE FROM words");
    query.exec("DELETE FROM documents");
}

// Добавление данных

bool DB::insertDocument(const QString &filePath)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO documents (file_path) VALUES (:path) "
                  "ON CONFLICT (file_path) DO NOTHING");
    query.bindValue(":path", filePath);
    if (!query.exec()) {
        qWarning() << "Insert document failed:" << query.lastError().text();
        return false;
    }
    return true;
}

int DB::getDocumentId(const QString &filePath)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT id FROM documents WHERE file_path = :path");
    query.bindValue(":path", filePath);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

bool DB::insertWord(const QString &word)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO words (word) VALUES (:word) ON CONFLICT (word) DO NOTHING");
    query.bindValue(":word", word);
    if (!query.exec()) {
        qWarning() << "Insert word failed:" << query.lastError().text();
        return false;
    }
    return true;
}

int DB::getWordId(const QString &word)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT id FROM words WHERE word = :word");
    query.bindValue(":word", word);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

bool DB::insertWordFrequency(int documentId, int wordId, int frequency)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO word_frequencies (document_id, word_id, frequency) "
                  "VALUES (:doc_id, :word_id, :freq) "
                  "ON CONFLICT (document_id, word_id) "
                  "DO UPDATE SET frequency = EXCLUDED.frequency");
    query.bindValue(":doc_id", documentId);
    query.bindValue(":word_id", wordId);
    query.bindValue(":freq", frequency);
    if (!query.exec()) {
        qWarning() << "Insert frequency failed:" << query.lastError().text();
        return false;
    }
    return true;
}
