#include "SpeedController.h"

SpeedController::SpeedController(QObject *parent)
    : QObject(parent), m_speed(0)  // 초기 속도는 0
{
    setupCanInterface();
}

SpeedController::~SpeedController() {
    // 소켓 종료 등 필요한 정리 작업
}

double SpeedController::speed() const {
    return m_speed;  // QML에서 속도 값을 읽기 위한 함수
}

void SpeedController::setupCanInterface()
{
    struct ifreq ifr;
    struct sockaddr_can addr;

    // 소켓 생성
    canSocket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (canSocket < 0) {
        std::cerr << "Error while opening socket" << std::endl;
        return;
    }

    // 네트워크 인터페이스 설정
    std::strcpy(ifr.ifr_name, "can0");
    ioctl(canSocket, SIOCGIFINDEX, &ifr);

    std::memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    // 소켓 바인딩
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
        // CAN 메시지에서 속도 값 추출
        int speed = (frame.data[0] << 8) | frame.data[1];
        double actualSpeed = speed / 10.0;  // 소수점 속도 처리

        // 속도 값이 변경되면 QML로 알림
        if (m_speed != actualSpeed) {
            m_speed = actualSpeed;
            emit speedChanged();  // 속도 변경 시 QML에 알림
        }
    }
}