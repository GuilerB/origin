#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{

}

void UDPworker::InitSocket()
{
    serviceUdpSocket = new QUdpSocket(this);
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);
    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);
}

void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{
    QByteArray data = datagram.data();
    
    if (data.size() > 0) {
        char messageType = data[0];
        
        if (messageType == 'T') {

            QDateTime dateTime;
            QByteArray timeData = data.mid(1);
            QDataStream timeStream(&timeData, QIODevice::ReadOnly);
            timeStream >> dateTime;
            emit sig_sendTimeToGUI(dateTime);
        } 
        else if (messageType == 'M') {

            QString message = QString::fromUtf8(data.mid(1));
            QString senderAddress = datagram.senderAddress().toString();
            qint64 messageSize = message.length();
            emit sig_sendMessageToGUI(message, senderAddress, messageSize);
        }
    }
}

void UDPworker::SendDatagram(QByteArray data)
{
    QByteArray messageWithType;
    messageWithType.append('T');
    messageWithType.append(data);
    serviceUdpSocket->writeDatagram(messageWithType, QHostAddress::LocalHost, BIND_PORT);
}

void UDPworker::SendMessageDatagram(QByteArray data, QString address, quint16 port)
{
    QByteArray messageWithType;
    messageWithType.append('M');
    messageWithType.append(data);
    serviceUdpSocket->writeDatagram(messageWithType, QHostAddress(address), port);
}

void UDPworker::readPendingDatagrams(void)
{
    while(serviceUdpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
        ReadDatagram(datagram);
    }
}
