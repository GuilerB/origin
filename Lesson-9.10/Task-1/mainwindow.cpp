#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client = new TCPclient(this);
    // поля по умолчанию
    ui->le_data->setEnabled(false);
    ui->pb_request->setEnabled(false);
    ui->lb_connectStatus->setText("Отключено");
    ui->lb_connectStatus->setStyleSheet("color: red");

    // сигналы
    connect(client, &TCPclient::sig_sendTime, this, &MainWindow::DisplayTime);
    connect(client, &TCPclient::sig_sendStat, this, &MainWindow::DisplayStat);
    connect(client, &TCPclient::sig_sendFreeSize, this, &MainWindow::DisplayFreeSpace);
    connect(client, &TCPclient::sig_SendReplyForSetData, this, &MainWindow::SetDataReply);
    connect(client, &TCPclient::sig_Error, this, &MainWindow::DisplayError);
    connect(client, &TCPclient::sig_Success, this, &MainWindow::DisplaySuccess);
    connect(client, &TCPclient::sig_connectStatus, this, &MainWindow::DisplayConnectStatus);
    
    //После отключения меняются доступности полей.
    connect(client, &TCPclient::sig_Disconnected, this, [&]{
        ui->lb_connectStatus->setText("Отключено");
        ui->lb_connectStatus->setStyleSheet("color: red");
        ui->pb_connect->setText("Подключиться");
        ui->le_data->setEnabled(false);
        ui->pb_request->setEnabled(false);
        ui->spB_port->setEnabled(true);
        ui->spB_ip1->setEnabled(true);
        ui->spB_ip2->setEnabled(true);
        ui->spB_ip3->setEnabled(true);
        ui->spB_ip4->setEnabled(true);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief Группа методо отображения различных данных
 */
void MainWindow::DisplayTime(QDateTime time)
{
    ui->tb_result->append("=== Время от сервера ===");
    ui->tb_result->append("Текущее время: " + time.toString("dd.MM.yyyy hh:mm:ss"));
    ui->tb_result->append("");
}

void MainWindow::DisplayFreeSpace(uint32_t freeSpace)
{
    ui->tb_result->append("=== Свободное место на сервере ===");
    ui->tb_result->append("Доступно байт: " + QString::number(freeSpace));
    ui->tb_result->append("");
}

void MainWindow::SetDataReply(QString replyString)
{
    ui->tb_result->append("=== Ответ на отправку данных ===");
    ui->tb_result->append("Сервер вернул: " + replyString);
    ui->tb_result->append("");
}

void MainWindow::DisplayStat(StatServer stat)
{
    ui->tb_result->append("=== Статистика сервера ===");
    ui->tb_result->append("Принято байт: " + QString::number(stat.incBytes));
    ui->tb_result->append("Передано байт: " + QString::number(stat.sendBytes));
    ui->tb_result->append("Принято пакетов: " + QString::number(stat.revPck));
    ui->tb_result->append("Передано пакетов: " + QString::number(stat.sendPck));
    ui->tb_result->append("Время работы: " + QString::number(stat.workTime) + " сек");
    ui->tb_result->append("Клиентов подключено: " + QString::number(stat.clients));
    ui->tb_result->append("");
}

void MainWindow::DisplayError(uint16_t error)
{
    switch (error) {
    case ERR_NO_FREE_SPACE:
        ui->tb_result->append("Ошибка: Недостаточно свободного места на сервере!");
        break;
    case ERR_CONNECT_TO_HOST:
        ui->tb_result->append("Ошибка подключения к серверу!");
        break;
    case ERR_NO_FUNCT:
        ui->tb_result->append("Ошибка: Функционал не реализован!");
        break;
    default:
        ui->tb_result->append("Неизвестная ошибка! Код: " + QString::number(error));
        break;
    }
    ui->tb_result->append("");
}

/*!
 * \brief Метод отображает квитанцию об успешно выполненном сообщениии
 * \param typeMess ИД успешно выполненного сообщения
 */
void MainWindow::DisplaySuccess(uint16_t typeMess)
{
    switch (typeMess) {
    case SET_DATA:
        ui->tb_result->append("Успех: Данные успешно отправлены на сервер!");
        break;
    case CLEAR_DATA:
        ui->tb_result->append("Успех: Память сервера успешно очищена!");
        break;
    default:
        ui->tb_result->append("Успех: Операция выполнена!");
        break;
    }
    ui->tb_result->append("");
}

/*!
 * \brief Метод отображает статус подключения
 */
void MainWindow::DisplayConnectStatus(uint16_t status)
{
    if(status == ERR_CONNECT_TO_HOST){
        ui->tb_result->append("Ошибка подключения к порту: " + QString::number(ui->spB_port->value()));
        ui->tb_result->append("");
    }
    else{
        ui->lb_connectStatus->setText("Подключено");
        ui->lb_connectStatus->setStyleSheet("color: green");
        ui->pb_connect->setText("Отключиться");
        ui->spB_port->setEnabled(false);
        ui->pb_request->setEnabled(true);
        ui->spB_ip1->setEnabled(false);
        ui->spB_ip2->setEnabled(false);
        ui->spB_ip3->setEnabled(false);
        ui->spB_ip4->setEnabled(false);
    }
}

/*!
 * \brief Обработчик кнопки подключения/отключения
 */
void MainWindow::on_pb_connect_clicked()
{
    if(ui->pb_connect->text() == "Подключиться"){
        uint16_t port = ui->spB_port->value();
        
        QString ip = ui->spB_ip4->text() + "." +
                     ui->spB_ip3->text() + "." +
                     ui->spB_ip2->text() + "." +
                     ui->spB_ip1->text();
        
        client->ConnectToHost(QHostAddress(ip), port);
    }
    else{
        client->DisconnectFromHost();
    }
}

/*
 * Для отправки сообщения согласно ПИВ необходимо
 * заполнить заголовок и передать его на сервер. В ответ
 * сервер вернет информацию в соответствии с типом сообщения
*/
void MainWindow::on_pb_request_clicked()
{
    ServiceHeader header;
    
    header.id = ID;
    header.status = STATUS_SUCCES;
    header.len = 0;
    
    switch (ui->cb_request->currentIndex()){

        case 0:
            header.idData = GET_TIME;
            client->SendRequest(header);
            ui->tb_result->append("Запрос времени отправлен...");
            break;           

        case 1:
            header.idData = GET_SIZE;
            client->SendRequest(header);
            ui->tb_result->append("Запрос свободного места отправлен...");
            break;
               
        case 2:
            header.idData = GET_STAT;
            client->SendRequest(header);
            ui->tb_result->append("Запрос статистики отправлен...");
            break;
            
        case 3:
            header.idData = SET_DATA;
            if(ui->le_data->text().isEmpty()){
                ui->tb_result->append("Ошибка: Введите данные для отправки!");
                ui->tb_result->append("");
                return;
            }
            client->SendData(header, ui->le_data->text());
            ui->tb_result->append("Отправка данных: \"" + ui->le_data->text() + "\"");
            break;            

        case 4:
            header.idData = CLEAR_DATA;
            client->SendRequest(header);
            ui->tb_result->append("Запрос на очистку памяти отправлен...");
            break;
            
        default:
            ui->tb_result->append("Такой запрос не реализован в текущей версии");
            ui->tb_result->append("");
            return;
    }
    ui->tb_result->append("");
}

/*!
 * \brief Обработчик изменения индекса запроса
 */
void MainWindow::on_cb_request_currentIndexChanged(int index)
{
    //Разблокировка поля отправления данных только когда выбрано "Отправить данные"
    if(ui->cb_request->currentIndex() == 3){
        ui->le_data->setEnabled(true);
    }
    else{
        ui->le_data->setEnabled(false);
    }
}
