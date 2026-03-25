#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tableModel(nullptr)
    , queryModel(nullptr)
{
    ui->setupUi(this);
    ui->lb_statusConnect->setStyleSheet("color:red");
    ui->pb_request->setEnabled(false);
    
    // Настройка таблицы
    ui->tb_result->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tb_result->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tb_result->horizontalHeader()->setStretchLastSection(true);
    
    dataDb = new DbData(this);
    dataBase = new DataBase(this);
    msg = new QMessageBox(this);
    
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);
    
    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);
    
    connect(dataDb, &DbData::sig_sendData, this, [&](QVector<QString> receivData){
        dataForConnect = receivData;
    });
    
    connect(dataBase, &DataBase::sig_SendDataFromDB, this, &MainWindow::ScreenDataFromDB);
    connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToDB);
    
    // Подключаем сигналы для кнопки очистки и комбобокса
    connect(ui->pb_clear, &QPushButton::clicked, this, &MainWindow::on_pb_clear_clicked);
    connect(ui->cb_category, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &MainWindow::on_cb_category_currentIndexChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(tableModel) delete tableModel;
    if(queryModel) delete queryModel;
}

void MainWindow::on_act_addData_triggered()
{
    dataDb->show();
}

void MainWindow::on_act_connect_triggered()
{
    if(ui->lb_statusConnect->text() == "Отключено"){
        ui->lb_statusConnect->setText("Подключение");
        ui->lb_statusConnect->setStyleSheet("color : black");
        
        auto conn = [&]{dataBase->ConnectToDataBase(dataForConnect);};
        QtConcurrent::run(conn);
    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        ui->lb_statusConnect->setText("Отключено");
        ui->act_connect->setText("Подключиться");
        ui->lb_statusConnect->setStyleSheet("color:red");
        ui->pb_request->setEnabled(false);
        
        // Очищаем модели при отключении
        if(tableModel) {
            tableModel->clear();
            ui->tb_result->setModel(nullptr);
        }
        if(queryModel) {
            queryModel->clear();
            ui->tb_result->setModel(nullptr);
        }
    }
}

void MainWindow::on_pb_request_clicked()
{
    // Получаем выбранную категорию
    int categoryIndex = ui->cb_category->currentIndex();

    if(categoryIndex == 0) {
        setupTableModel();
    } else if(categoryIndex == 1) {
        setupQueryModel("Comedy");
    } else if(categoryIndex == 2) {
        setupQueryModel("Horror");
    }
}

void MainWindow::setupTableModel()
{
    // Очищаем предыдущее состояние. Столбцы могут иначе быть в неверном порядке
    ui->tb_result->setModel(nullptr);
    ui->tb_result->horizontalHeader()->reset();

    // Получаем соединение с БД
    QSqlDatabase db = QSqlDatabase::database(DB_NAME);
    if(!db.isOpen()) {
        msg->setText("База данных не открыта!");
        msg->exec();
        return;
    }

    // Создаем и настраиваем QSqlTableModel
    if(tableModel) delete tableModel;
    tableModel = new QSqlTableModel(this, db);
    tableModel->setTable("film");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();

    if(tableModel->lastError().isValid()) {
        msg->setText("Ошибка загрузки данных: " + tableModel->lastError().text());
        msg->exec();
        return;
    }

    int titleColumn = tableModel->fieldIndex("title");
    int descriptionColumn = tableModel->fieldIndex("description");

    tableModel->setHeaderData(titleColumn, Qt::Horizontal, "Название фильма");
    tableModel->setHeaderData(descriptionColumn, Qt::Horizontal, "Описание фильма");

    ui->tb_result->setModel(tableModel);

    // Скрываем все столбцы
    for(int i = 0; i < tableModel->columnCount(); ++i) {
        ui->tb_result->setColumnHidden(i, true);
    }

    ui->tb_result->showColumn(titleColumn);
    ui->tb_result->showColumn(descriptionColumn);

    // Настройка размеров
    ui->tb_result->resizeColumnsToContents();
    ui->tb_result->horizontalHeader()->setStretchLastSection(true);
    ui->tb_result->setColumnWidth(ui->tb_result->horizontalHeader()->visualIndex(titleColumn), 200);
    ui->tb_result->setColumnWidth(ui->tb_result->horizontalHeader()->visualIndex(descriptionColumn), 450);
}

void MainWindow::setupQueryModel(const QString& category)
{
    // Очищаем предыдущее состояние. Столбцы могут иначе быть в неверном порядке
    ui->tb_result->setModel(nullptr);
    ui->tb_result->horizontalHeader()->reset();

    // Получаем соединение с БД
    QSqlDatabase db = QSqlDatabase::database(DB_NAME);
    if(!db.isOpen()) {
        msg->setText("База данных не открыта!");
        msg->exec();
        return;
    }

    QString queryStr = "SELECT f.title, f.description FROM film f "
                       "JOIN film_category fc ON f.film_id = fc.film_id "
                       "JOIN category c ON c.category_id = fc.category_id "
                       "WHERE c.name = '" + category + "'";

    if(queryModel) delete queryModel;
    queryModel = new QSqlQueryModel(this);
    queryModel->setQuery(queryStr, db);

    if(queryModel->lastError().isValid()) {
        msg->setText("Ошибка запроса: " + queryModel->lastError().text());
        msg->exec();
        return;
    }

    queryModel->setHeaderData(0, Qt::Horizontal, "Название фильма");
    queryModel->setHeaderData(1, Qt::Horizontal, "Описание фильма");

    ui->tb_result->setModel(queryModel);

    // Настраиваем размеры
    ui->tb_result->resizeColumnsToContents();
    ui->tb_result->horizontalHeader()->setStretchLastSection(true);
    ui->tb_result->setColumnWidth(0, 200);
    ui->tb_result->setColumnWidth(1, 450);
}
void MainWindow::on_pb_clear_clicked()
{
    // Очищаем модель
    if(tableModel) {
        tableModel->clear();
    }
    if(queryModel) {
        queryModel->clear();
    }

    // Сбрасываем модель из представления
    ui->tb_result->setModel(nullptr);

    // Очищаем статусбар
    ui->statusbar->clearMessage();
}

void MainWindow::on_cb_category_currentIndexChanged(int index)
{
    // Если БД подключена, автоматически обновляем данные при смене категории
    if(ui->lb_statusConnect->text() == "Подключено к БД" && index >= 0) {
        on_pb_request_clicked();
    }
}

void MainWindow::ScreenDataFromDB(const QTableWidget *widget, int typeRequest)
{
    Q_UNUSED(widget);
    Q_UNUSED(typeRequest);
}

void MainWindow::ReceiveStatusConnectionToDB(bool status)
{
    if(status){
        ui->act_connect->setText("Отключиться");
        ui->lb_statusConnect->setText("Подключено к БД");
        ui->lb_statusConnect->setStyleSheet("color:green");
        ui->pb_request->setEnabled(true);
        
        on_pb_request_clicked();
    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->GetLastError().text());
        ui->lb_statusConnect->setText("Отключено");
        ui->lb_statusConnect->setStyleSheet("color:red");
        msg->exec();
    }
}
