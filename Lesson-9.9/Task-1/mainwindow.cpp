#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendMessageToGUI, this, &MainWindow::DisplayMessage);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}

void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));
}

void MainWindow::DisplayMessage(QString message, QString senderAddress, qint64 messageSize)
{
    ui->te_result->append(QString("Принято сообщение от %1, размер сообщения(байт) %2")
                         .arg(senderAddress)
                         .arg(messageSize));
}

void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}

void MainWindow::on_pb_sendMessage_clicked()
{
    QString messageText = ui->le_message->text();
    
    if (messageText.isEmpty()) {
        return;
    }
    
    QByteArray dataToSend = messageText.toUtf8();
    udpWorker->SendMessageDatagram(dataToSend, "127.0.0.1", BIND_PORT);
    ui->le_message->clear();
}
