// SpeedController.h

#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H

#include <QObject>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <net/if.h>
#include <cstring>
#include <iostream>

class SpeedController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)  // QML과 상호작용할 속성

public:
    explicit SpeedController(QObject *parent = nullptr);
    ~SpeedController();

    double speed() const;   // QML에서 속도 값을 읽기 위한 getter 함수

signals:
    void speedChanged();   // QML에 속도 값이 변경되었음을 알리는 시그널

public slots:
    void updateSpeed();  // CAN에서 속도를 받아 업데이트하는 함수

private:
    int canSocket;
    double m_speed;  // 속도를 저장하는 멤버 변수

    void setupCanInterface();  // CAN 인터페이스 설정 함수
};

#endif // SPEEDCONTROLLER_H