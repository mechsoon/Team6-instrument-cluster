#include "SpeedController.h"

SpeedController::SpeedController(QObject *parent)
    : QObject(parent), m_speed(0), ema_speed(0), alpha(0.1), canSocket(-1)  // 초기 ema_speed 추가
{
    setupCanInterface();
    timer = new QTimer(this);
    timer->start(100);
    qDebug() << "Timer started, updating every 100ms";
    connect(timer, &QTimer::timeout, this, &SpeedController::updateSpeed);
}

SpeedController::~SpeedController() {
    if (canSocket >= 0) {
        close(canSocket);
    }
}

double SpeedController::speed() const {
    return ema_speed;  // EMA 필터가 적용된 속도를 반환
}

void SpeedController::setupCanInterface() {
    struct ifreq ifr;
    struct sockaddr_can addr;

    canSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (canSocket < 0) {
        std::cerr << "Error while opening socket" << std::endl;
        return;
    }

    std::strcpy(ifr.ifr_name, "can0");
    if (ioctl(canSocket, SIOCGIFINDEX, &ifr) < 0) {
        std::cerr << "Error in ioctl" << std::endl;
        close(canSocket);
        canSocket = -1;
        return;
    }

    std::memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(canSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error in socket bind" << std::endl;
        close(canSocket);
        canSocket = -1;
        return;
    }
}

void SpeedController::updateSpeed() {
    qDebug() << "updateSpeed() called";
    struct can_frame frame;
    int nbytes = read(canSocket, &frame, sizeof(struct can_frame));
    if (nbytes < 0) {
        std::cerr << "Error reading from CAN socket" << std::endl;
        return;
    }
    if (nbytes > 0 && frame.can_id == 0x100) { 
        double new_speed = (frame.data[0] << 8) | frame.data[1];  // 새로 수신된 속도
        qDebug() << "Received speed:" << new_speed;

        // EMA 필터 적용
        ema_speed = alpha * new_speed + (1 - alpha) * ema_speed;

        qDebug() << "Filtered speed (EMA):" << ema_speed;

        if (m_speed != ema_speed) {
            m_speed = ema_speed;
            emit speedChanged();  // 필터된 속도가 변할 경우 시그널 발생
        }
    }
}
