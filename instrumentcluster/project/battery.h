#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>

class Battery: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int battery READ battery NOTIFY batteryChanged)
public:
    explicit Battery(QObject *parent = nullptr);
    ~Battery();
    int battery();

signals:
    void batteryChanged();

public slots:
    void onNewConnection();

private:
    QTcpServer *server;
    int m_battery;
    QTimer *timer;
};

#endif // BATTERY_H
