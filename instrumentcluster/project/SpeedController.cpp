#include "SpeedController.h"

SpeedController::SpeedController(QObject *parent)
    : QObject(parent), m_speed(0) 
{
    setupCanInterface();

    connect(timer, &QTimer::timeout, this, &SpeedController::updateSpeed);
    timer->start(100);  
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
    ioctl(canSocket, SIOCGIFINDEX, &ifr);

    std::memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(canSocket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error in socket bind" << std::endl;
        return;
    }
}

void SpeedController::updateSpeed()
{
    struct can_frame frame;
    int nbytes = read(canSocket, &frame, sizeof(struct can_frame));

    if (nbytes > 0 && frame.can_id == 0x100) {

        int speed = frame.data[0];

        if (m_speed != speed) {
            m_speed = speed;
            emit speedChanged();  
        }
    }
}
