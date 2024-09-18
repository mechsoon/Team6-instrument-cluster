#ifndef SPEEDCONTROL_H
#define SPEEDCONTROL_H

#include <QObject>
#include <QDebug>
#include "canreceiver.h"

class SpeedController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)

public:
    explicit SpeedController(QObject *parent = nullptr);
    ~SpeedController();

    double speed() const;

signals:
    void speedChanged();

public slots:
    void handleSpeedUpdate(double speed);

private:
    double m_speed;
    CanReceiver *canreceiver;
};

#endif // SPEEDCONTROLLER_H


