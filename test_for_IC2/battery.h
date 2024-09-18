#include <QObject>
#include <QDebug>
#include <fcntl.h>  // For open()
#include <unistd.h> // For read() and write()
#include <sys/ioctl.h> // For ioctl()
#include <linux/i2c-dev.h> // For I2C definitions
#include <QTimer>





class I2CIna219 : public QObject {
    Q_OBJECT
    Q_PROPERTY(int level READ level NOTIFY batteryChanged)

public:
    explicit I2CIna219(QObject *parent = nullptr);
    ~I2CIna219();
    bool initI2C();
    void readBusVoltage();
    int level();
    double get_battery_soc(double voltage);
signals:
        void batteryChanged();

private:
    const char *device;
    int ina219Address;
    int busVoltageRegister;
    int file;
    int m_level;
    QTimer *timer;



};
