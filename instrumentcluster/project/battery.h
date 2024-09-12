#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

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
};

#endif // BATTERY_H
