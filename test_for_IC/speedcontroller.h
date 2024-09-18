#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H

#include <QObject>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <cstring>
#include <iostream>
#include <QTimer>
#include <unistd.h>
#include <QDebug>

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
    void updateSpeed();  // 속도를 업데이트하는 함수

private:
    int canSocket;
    double m_speed;

    void setupCanInterface();  // CAN 인터페이스 설정 함수
};

#endif // SPEEDCONTROLLER_H
