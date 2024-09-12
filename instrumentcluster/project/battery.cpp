#include "battery.h"

Battery::Battery(QObject *parent)
    : QObject(parent)
{
    server=new QTcpServer(this);
    if (!server->listen(QHostAddress::LocalHost, 12345)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
    connect(server, &QTcpServer::newConnection, this, &Battery::onNewConnection);
}


void Battery::onNewConnection(){
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, [=]() {
        QByteArray data = socket->readAll();
        int receivedInt = QString(data).toInt();
        qDebug() << "Received integer:" << receivedInt;
    });
}

int Battery::battery(){
    return m_battery;
}
