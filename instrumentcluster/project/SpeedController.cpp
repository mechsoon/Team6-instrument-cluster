#include "SpeedController.h"

SpeedController::SpeedController(QObject *parent)
    : QObject(parent), m_speed(-28) , canSocket(-1)
{
    setupCanInterface();
    timer=new QTimer(this);
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
    return m_speed;  
}

void SpeedController::setupCanInterface()
{
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
        close(canSocket);  // 오류 시 소켓 닫기
        canSocket = -1;
        return;
    }

    std::memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(canSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error in socket bind" << std::endl;
        close(canSocket);
        canSocket=-1;
        return;
    }
}

void SpeedController::updateSpeed()
{
    qDebug() << "updateSpeed() called";
    struct can_frame frame;
    int nbytes = read(canSocket, &frame, sizeof(struct can_frame));
    if (nbytes < 0) {
        std::cerr << "Error reading from CAN socket" << std::endl;
        return;
    }
    if (nbytes > 0 && frame.can_id == 0x100) {
        
        double speed = frame.data[0];
        qDebug() << "Received speed:" << speed;
        if (m_speed != speed) {
            m_speed = speed;
            emit speedChanged();  
        }
    }
}
