#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "speedcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // SpeedController 객체 생성
    SpeedController speedController;

    // SpeedController 객체를 QML에 등록
    engine.rootContext()->setContextProperty("speedController", &speedController);

    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
