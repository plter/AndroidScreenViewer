#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "adbprocess.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<AdbProcess>("AdbProcess",1,0,"AdbProcess");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

