#include "speedcontrol.h"

SpeedController::SpeedController(QObject *parent)
    : QObject(parent), m_speed(0)
{
    canreceiver = new CanReceiver(this);

    connect(canreceiver, &CanReceiver::speedUpdated, this, &SpeedController::handleSpeedUpdate);
}

SpeedController::~SpeedController() {
    delete canreceiver;
}

double SpeedController::speed() const {
    return m_speed;
}

void SpeedController::handleSpeedUpdate(double speed)
{
    qDebug() << "SpeedController received speed:" << speed;
    if (m_speed != speed) {
        m_speed = speed;
        emit speedChanged();
    }
}
