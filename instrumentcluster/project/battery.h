#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>
#include <QDebug>
class Battery: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double battery READ battery NOTIFY batteryChanged)
public:
    explicit Battery(QObject *parent = nullptr);
    ~Battery();
    double battery();

signals:
    void batteryChanged();

public slots:
    void onNewConnection();

private:
    QTcpServer *server;
    double m_battery;
    QTimer *timer;
};

#endif // BATTERY_H
