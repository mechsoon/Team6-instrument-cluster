#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "speedcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // SpeedController 객체 생성 및 QML에 등록
    SpeedController speedController;
    engine.rootContext()->setContextProperty("speedController", &speedController);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    // CAN 데이터를 주기적으로 업데이트하는 타이머 설정
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &speedController, &SpeedController::updateSpeed);
    timer.start(1000);  // 1초마다 업데이트

    return app.exec();
}
