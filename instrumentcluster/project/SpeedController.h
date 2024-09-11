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

class SpeedController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)

public:
    explicit SpeedController(QObject *parent = nullptr);
    ~SpeedController();

    double speed() const; 

signals:
    void speedChanged(int);  

public slots:
    void updateSpeed(int); 

    
private:
    int canSocket;
    double m_speed;  
    QTimer *timer;  
    void setupCanInterface(); 
};

#endif // SPEEDCONTROLLER_H
