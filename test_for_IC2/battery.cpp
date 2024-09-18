#include "battery.h"

I2CIna219::I2CIna219(QObject *parent)
    : QObject(parent), device("/dev/i2c-1"), ina219Address(0x41), busVoltageRegister(0x02), file(-1),m_level(0) {
    initI2C();
    timer=new QTimer(this);
    timer->start(60000);
    // updated battery every 1min";
    connect(timer, &QTimer::timeout, this, &I2CIna219::readBusVoltage);
}

I2CIna219::~I2CIna219() {
    if (file >= 0) {
        close(file);
    }
}

std::map<float, float> voltage_to_soc = {
    {12.6, 100.0},
    {12.4, 90.0},
    {12.2, 80.0},
    {12.0, 70.0},
    {11.8, 60.0},
    {11.6, 50.0},
    {11.4, 40.0},
    {11.2, 30.0},
    {11.0, 20.0},
    {10.8, 10.0},
    {10.5, 5.0},
    {9.0, 0.0}
};
double I2CIna219::get_battery_soc(double voltage) {

    if (voltage >= 12.6) {
        return 100.0;
    } else if (voltage <= 9.0) {
        return 0.0;
    }


    auto it_high = voltage_to_soc.lower_bound(voltage);
    if (it_high == voltage_to_soc.end()) return 0.0;

    auto it_low = std::prev(it_high);

    float v_high = it_high->first;
    float soc_high = it_high->second;
    float v_low = it_low->first;
    float soc_low = it_low->second;


    return soc_low + (soc_high - soc_low) * (voltage - v_low) / (v_high - v_low);
}

bool I2CIna219::initI2C() {

    file = open(device, O_RDWR);
    if (file < 0) {
        qDebug() << "Cannot open I2C device";
        return false;
    }


    if (ioctl(file, I2C_SLAVE, ina219Address) < 0) {
        qDebug() << "Failed to set I2C slave address";
        return false;
    }

    return true;
}

int I2CIna219::level(){
    return m_level;
}

void I2CIna219::readBusVoltage() {
    if (file < 0) {
        qDebug() << "I2C device not initialized";
        // return -1;
    }


    char buf[2] = {busVoltageRegister};
    if (write(file, buf, 1) != 1) {
        qDebug() << "Failed to write to I2C";
        // return -1;
    }

    if (read(file, buf, 2) != 2) {
        qDebug() << "Failed to read from I2C";
        // return -1;
    }


    int16_t rawVoltage = (buf[0] << 8) | buf[1];
    rawVoltage >>= 3;
    double busVoltage = rawVoltage * 0.004;
    int voltage=get_battery_soc(busVoltage);
    m_level=voltage;
    emit batteryChanged();

}
