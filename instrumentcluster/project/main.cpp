#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "SpeedController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    SpeedController speedController;
    engine.rootContext()->setContextProperty("speedController", &speedController);

    // qmlRegisterType<SpeedController>("com.example.speedcontroller", 1, 0, "SpeedController");
    // 메인 QML 파일 경로 설정
    const QUrl url(u"qrc:/Main.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);  // Main.qml 로드

    return app.exec();
}
