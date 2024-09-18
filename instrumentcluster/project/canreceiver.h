#ifndef CANRECEIVER_H
#define CANRECEIVER_H

#include <QObject>
#include <QtSerialBus/QCanBus>
#include <QtSerialBus/QCanBusDevice>
#include <QDebug>

class CanReceiver : public QObject
{
    Q_OBJECT

public:
    explicit CanReceiver(QObject *parent = nullptr);
    ~CanReceiver();

signals:
    void speedUpdated(double speed);

public slots:
    void processCanFrame();

private:
    QCanBusDevice *canDevice;
    void setupCanInterface();
};

#endif // CANWORKER_H
