#include "battery.h"

Battery::Battery(QObject *parent)
    : QObject(parent),m_battery(0)
{
    server=new QTcpServer(this);

    if (!server->listen(QHostAddress::LocalHost, 12345)) {
        qDebug() << "Server could not start!";
    } else {

        qDebug() << "Server started!";
    }

    bool check=connect(server, &QTcpServer::newConnection, this, &Battery::onNewConnection);
    qDebug()<<check;

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

double Battery::battery(){
    return m_battery;
}
