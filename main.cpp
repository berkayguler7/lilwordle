#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "wordlegame.h"

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // high dpi scaling is now enabled by default
    QGuiApplication app(argc, argv);

    qmlRegisterType<WordleGame>("WordleGame", 1, 0, "WordleGame");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
