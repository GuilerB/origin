#include "tcpclient.h"

/* ServiceHeader
 * Для работы с потоками наши данные необходимо сериализовать.
 * Поскольку типы данных не стандартные перегрузим оператор << Для работы с ServiceHeader
*/
QDataStream &operator >>(QDataStream &out, ServiceHeader &data){
    out >> data.id;
    out >> data.idData;
    out >> data.status;
    out >> data.len;
    return out;
};

QDataStream &operator <<(QDataStream &in, ServiceHeader &data){
    in << data.id;
    in << data.idData;
    in << data.status;
    in << data.len;
    return in;
};

// Оператор для чтения StatServer из потока
QDataStream &operator >>(QDataStream &in, StatServer &data){
    in >> data.incBytes;
    in >> data.sendBytes;
    in >> data.revPck;
    in >> data.sendPck;
    in >> data.workTime;
    in >> data.clients;
    return in;
};

// Оператор для записи StatServer в поток
QDataStream &operator <<(QDataStream &in, StatServer &data){
    in << data.incBytes;
    in << data.sendBytes;
    in << data.revPck;
    in << data.sendPck;
    in << data.workTime;
    in << data.clients;
    return in;
};

/*
 * Поскольку мы являемся клиентом, инициализацию сокета
 * проведем в конструкторе. Также необходимо соединить
 * сокет со всеми необходимыми нам сигналами.
*/
TCPclient::TCPclient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    servHeader.idData = 0;
    servHeader.status = 0;
    servHeader.len = 0;

    connect(socket, &QTcpSocket::readyRead, this, &TCPclient::ReadyReed);
    connect(socket, &QTcpSocket::connected, this, [&](){
        emit sig_connectStatus(STATUS_SUCCES);
    });
    connect(socket, &QTcpSocket::disconnected, this, [&](){
        emit sig_Disconnected();
    });
    connect(socket, &QTcpSocket::errorOccurred, this, [&](QAbstractSocket::SocketError error){
        Q_UNUSED(error);
        emit sig_connectStatus(ERR_CONNECT_TO_HOST);
    });
}

/* write
 * Метод отправляет запрос на сервер. Сериализировать будем
 * при помощи QDataStream
*/
void TCPclient::SendRequest(ServiceHeader head)
{
    if(socket->state() != QAbstractSocket::ConnectedState){
        emit sig_Error(ERR_CONNECT_TO_HOST);
        return;
    }

    QByteArray dataBlock;
    QDataStream out(&dataBlock, QIODevice::WriteOnly);
    out << head;
    socket->write(dataBlock);
}

/* write
 * Такой же метод только передаем еще данные.
*/
void TCPclient::SendData(ServiceHeader head, QString str)
{
    if(socket->state() != QAbstractSocket::ConnectedState){
        emit sig_Error(ERR_CONNECT_TO_HOST);
        return;
    }

    QByteArray dataBlock;
    QDataStream out(&dataBlock, QIODevice::WriteOnly);

    head.len = str.toUtf8().size();
    out << head;
    out << str;

    socket->write(dataBlock);
}

/*
 * \brief Метод подключения к серверу
 */
void TCPclient::ConnectToHost(QHostAddress host, uint16_t port)
{
    if(socket->state() != QAbstractSocket::ConnectedState){
        socket->connectToHost(host, port);
    }
}

/*
 * \brief Метод отключения от сервера
 */
void TCPclient::DisconnectFromHost()
{
    if(socket->state() == QAbstractSocket::ConnectedState){
        socket->disconnectFromHost();
    }
}

void TCPclient::ReadyReed()
{
    QDataStream incStream(socket);

    if(incStream.status() != QDataStream::Ok){
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Ошибка открытия входящего потока для чтения данных!");
        msg.exec();
        return;
    }

    //Читаем до конца потока
    while(incStream.atEnd() == false){
        //Если мы обработали предыдущий пакет, мы скинули значение idData в 0
        if(servHeader.idData == 0){
            //Проверяем количество полученных байт. Если доступных байт меньше чем
            //заголовок, то выходим из обработчика и ждем новую посылку
            if(socket->bytesAvailable() < sizeof(ServiceHeader)){
                return;
            }
            else{
                //Читаем заголовок
                incStream >> servHeader;
                //Проверяем на корректность данных
                if(servHeader.id != ID){
                    uint16_t hdr = 0;
                    while(!incStream.atEnd()){
                        incStream >> hdr;
                        if(hdr == ID){
                            servHeader.id = hdr;
                            incStream >> servHeader.idData;
                            incStream >> servHeader.status;
                            incStream >> servHeader.len;
                            break;
                        }
                    }
                }
            }
        }
        //Если получены не все данные, то выходим из обработчика
        if(socket->bytesAvailable() < servHeader.len){
            return;
        }
        else{

            ProcessingData(servHeader, incStream);
            servHeader.idData = 0;
            servHeader.status = 0;
            servHeader.len = 0;
        }
    }
}

void TCPclient::ProcessingData(ServiceHeader header, QDataStream &stream)
{
    switch (header.idData){
        case GET_TIME:{
            QDateTime time;
            stream >> time;
            emit sig_sendTime(time);
            break;
        }
        case GET_SIZE:{
            uint32_t freeSpace;
            stream >> freeSpace;
            emit sig_sendFreeSize(freeSpace);
            break;
        }
        case GET_STAT:{
            StatServer stat;
            stream >> stat;
            emit sig_sendStat(stat);
            break;
        }
        case SET_DATA:{
            QString replyStr;
            stream >> replyStr;
            emit sig_SendReplyForSetData(replyStr);
            if(header.status == STATUS_SUCCES){
                emit sig_Success(SET_DATA);
            } else {
                emit sig_Error(header.status);
            }
            break;
        }
        case CLEAR_DATA:{
            if(header.status == STATUS_SUCCES){
                emit sig_Success(CLEAR_DATA);
            } else {
                emit sig_Error(header.status);
            }
            break;
        }
        default:
            return;
    }
}
