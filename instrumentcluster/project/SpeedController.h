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
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)

public:
    explicit SpeedController(QObject *parent = nullptr);
    ~SpeedController();

    int speed() const;

signals:
    void speedChanged();

public slots:
    void updateSpeed();

    
private:
    int canSocket;
    double m_speed;
    int ema_speed;
    double alpha;
    QTimer *timer;  
    void setupCanInterface(); 
};

#endif // SPEEDCONTROLLER_H
