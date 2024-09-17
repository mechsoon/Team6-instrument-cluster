#include "SpeedController.h"
#include <cmath> // for abs

SpeedController::SpeedController(QObject *parent)
    : QObject(parent), m_speed(0), canSocket(-1), 
      estimatedSpeed(0), // 칼만 필터의 초기 추정 속도
      errorCovariance(1), // 초기 오차 공분산 (대략적인 값)
      processNoise(1e-2), // 시스템 잡음 (필터의 반응 속도를 조절)
      measurementNoise(1e-1) // 측정 잡음 (노이즈 수준에 맞춰 조정)
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
    return m_speed;
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
        double measuredSpeed = (frame.data[0] << 8) | frame.data[1];
        qDebug() << "Received speed:" << measuredSpeed;

        // 칼만 필터 적용
        applyKalmanFilter(measuredSpeed);

        if (m_speed != estimatedSpeed) {
            m_speed = estimatedSpeed; //estimatedSpeed가 기존 스피드에서 칼만 필터를 적용시킨 스피드.
            emit speedChanged();
        }
    }
}

void SpeedController::applyKalmanFilter(double measuredSpeed) {
    // 1. 예측 단계
    // 속도는 변하지 않는다고 가정 (모델 단순화)
    // 이 단계에서는 추정된 속도는 변화가 없으며, 오차 공분산만 증가
    errorCovariance += processNoise;

    // 2. 칼만 이득 계산
    double kalmanGain = errorCovariance / (errorCovariance + measurementNoise);

    // 3. 갱신 단계
    // 새로운 측정값을 반영하여 추정 속도와 오차 공분산을 갱신
    estimatedSpeed = estimatedSpeed + kalmanGain * (measuredSpeed - estimatedSpeed);
    errorCovariance = (1 - kalmanGain) * errorCovariance;

    // 디버깅 정보 출력
    qDebug() << "Filtered speed (Kalman):" << estimatedSpeed;
}
