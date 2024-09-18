#include "canreceiver.h"


CanReceiver::CanReceiver(QObject *parent) : QObject(parent), canDevice(nullptr)
{
    setupCanInterface();
}

CanReceiver::~CanReceiver() {
    if (canDevice && canDevice->state() == QCanBusDevice::ConnectedState) {
        canDevice->disconnectDevice();
    }
    delete canDevice;
}

void CanReceiver::setupCanInterface()
{
    QString errorString;

    canDevice = QCanBus::instance()->createDevice("socketcan", "can0", &errorString);
    if (!canDevice) {
        qDebug() << "Error creating CAN device:" << errorString;
        return;
    }

    if (canDevice->connectDevice()) {
        qDebug() << "CAN device connected successfully";

        connect(canDevice, &QCanBusDevice::framesReceived, this, &CanReceiver::processCanFrame);
    } else {
        qDebug() << "Failed to connect CAN device:" << canDevice->errorString();
    }
}

void CanReceiver::processCanFrame()
{

    while (canDevice->framesAvailable()) {
        QCanBusFrame frame = canDevice->readFrame();
        if (frame.frameId() == 0x100) {
            QByteArray payload = frame.payload();
            if (payload.size() >= 2) {
                double speed = (static_cast<uint8_t>(payload[0]) << 8) | static_cast<uint8_t>(payload[1]);
                qDebug() << "CANWorker received speed:" << speed;
                emit speedUpdated(speed);
            }
        }
    }
}

