#include "SpeedController2.h"

SpeedController::SpeedController(QObject *parent)
    : QObject(parent), m_speed(0), filteredSpeed(0), canSocket(-1), emaEnabled(false), kalmanEnabled(false)
{
    setupCanInterface();
    timer = new QTimer(this);
    timer->start(100);
    qDebug() << "Timer started, updating every 100ms";
    connect(timer, &QTimer::timeout, this, &SpeedController::updateSpeed);

    // Initialize Kalman filter variables
    kalmanX = 0.0;    // Estimated value
    kalmanP = 1.0;    // Estimate error
    kalmanQ = 0.01;   // Process noise covariance
    kalmanR = 0.1;    // Measurement noise covariance
}

SpeedController::~SpeedController() {
    if (canSocket >= 0) {
        close(canSocket);
    }
}

double SpeedController::speed() const {
    return filteredSpeed;
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
        double speed = (frame.data[0] << 8) | frame.data[1];
        qDebug() << "Received speed:" << speed;

        // Apply the chosen filter
        if (emaEnabled) {
            filteredSpeed = applyEMA(speed);
        } else if (kalmanEnabled) {
            filteredSpeed = applyKalman(speed);
        } else {
            filteredSpeed = speed;
        }

        if (m_speed != filteredSpeed) {
            m_speed = filteredSpeed;
            emit speedChanged();
        }
    }
}

double SpeedController::applyEMA(double newSpeed)
{
    const double alpha = 0.3;
    filteredSpeed = alpha * newSpeed + (1 - alpha) * filteredSpeed;
    return filteredSpeed;
}

double SpeedController::applyKalman(double newSpeed)
{
    // Prediction update
    kalmanP = kalmanP + kalmanQ;

    // Measurement update
    double K = kalmanP / (kalmanP + kalmanR);
    kalmanX = kalmanX + K * (newSpeed - kalmanX);
    kalmanP = (1 - K) * kalmanP;

    return kalmanX;
}

// Enable/Disable EMA filter
void SpeedController::enableEMA(bool enabled)
{
    emaEnabled = enabled;
    if (enabled) kalmanEnabled = false;  // Disable Kalman if EMA is enabled
}

// Enable/Disable Kalman filter
void SpeedController::enableKalman(bool enabled)
{
    kalmanEnabled = enabled;
    if (enabled) emaEnabled = false;  // Disable EMA if Kalman is enabled
}
