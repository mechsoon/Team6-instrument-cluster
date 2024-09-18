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
    // SocketCAN 드라이버를 사용하고 "can0" 인터페이스 설정
    canDevice = QCanBus::instance()->createDevice("socketcan", "can0", &errorString);
    if (!canDevice) {
        qDebug() << "Error creating CAN device:" << errorString;
        return;
    }

    // CAN 장치 연결
    if (canDevice->connectDevice()) {
        qDebug() << "CAN device connected successfully";

        // CAN 데이터가 수신될 때마다 processCanFrame 슬롯 호출
        connect(canDevice, &QCanBusDevice::framesReceived, this, &CanReceiver::processCanFrame);
    } else {
        qDebug() << "Failed to connect CAN device:" << canDevice->errorString();
    }
}

void CanReceiver::processCanFrame()
{
    // 수신된 모든 프레임 처리
    while (canDevice->framesAvailable()) {
        QCanBusFrame frame = canDevice->readFrame();
        if (frame.frameId() == 0x100) {  // CAN ID 0x100을 확인
            QByteArray payload = frame.payload();
            if (payload.size() >= 2) {  // 최소 2바이트가 있어야 함
                double speed = (static_cast<uint8_t>(payload[0]) << 8) | static_cast<uint8_t>(payload[1]);
                qDebug() << "CANWorker received speed:" << speed;
                emit speedUpdated(speed);  // 속도 업데이트 시그널 발신
            }
        }
    }
}

