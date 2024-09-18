#ifndef SPEEDCONTROLLER2_H
#define SPEEDCONTROLLER2_H

#include <QObject>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
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
    void updateSpeed();
    void enableEMA(bool enabled);      // EMA 필터 활성화/비활성화 슬롯
    void enableKalman(bool enabled);   // 칼만 필터 활성화/비활성화 슬롯

private:
    int canSocket;
    double m_speed;
    double filteredSpeed;  // 필터링된 속도 값
    QTimer *timer;

    // EMA 필터 변수
    bool emaEnabled;
    double applyEMA(double newSpeed);

    // 칼만 필터 변수
    bool kalmanEnabled;
    double kalmanX;   // 칼만 필터의 추정 값
    double kalmanP;   // 추정 오차 공분산
    double kalmanQ;   // 프로세스 노이즈 공분산
    double kalmanR;   // 측정 노이즈 공분산
    double applyKalman(double newSpeed);

    void setupCanInterface();
};

#endif // SPEEDCONTROLLER_H
