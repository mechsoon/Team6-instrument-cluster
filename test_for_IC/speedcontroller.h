#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H

#include <QObject>
#include <QTimer>
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

    // EMA 필터 활성화/비활성화 함수
    Q_INVOKABLE void toggleEmaFilter(bool enabled);

    // 칼만 필터 활성화/비활성화 함수
    Q_INVOKABLE void toggleKalmanFilter(bool enabled);

signals:
    void speedChanged();

private slots:
    void updateSpeed();

private:
    void setupCanInterface();
    double applyKalmanFilter(double measurement);  // 칼만 필터 함수

    int canSocket;
    double m_speed;

    // EMA 필터 관련 멤버 변수
    double ema_speed;  // EMA 필터에 사용되는 속도 값
    double alpha;  // EMA 필터의 알파 값
    bool useEmaFilter;  // EMA 필터 활성화 여부

    // 칼만 필터 관련 멤버 변수
    bool useKalmanFilter;  // 칼만 필터 활성화 여부
};

#endif // SPEEDCONTROLLER_H
