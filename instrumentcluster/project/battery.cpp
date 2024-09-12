#include "battery.h"

Battery::Battery(QObject *parent)
    : QObject(parent)
{
    server=new QTcpServer(this);
    timer=new QTimer(this);
    timer->start(5000);
    if (!server->listen(QHostAddress::LocalHost, 12345)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }

    connect(timer, &QTimer::timeout, server, &QTcpServer::newConnection);
    connect(server, &QTcpServer::newConnection, this, &Battery::onNewConnection);


}


void Battery::onNewConnection(){
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, [=]() {
        QByteArray data = socket->readAll();
        int receivedInt = QString(data).toInt();
        m_battery=receivedInt;
        qDebug() << "Received integer:" << receivedInt;
    });
    emit batteryChanged();
}

Battery::~Battery(){}

int Battery::battery(){
    return m_battery;
}
