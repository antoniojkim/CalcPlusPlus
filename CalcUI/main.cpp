#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    QObject *rootObject = engine.rootObjects().first();
    QObject *qmlObject = rootObject->findChild<QObject*>("input1");

    cout << qmlObject << endl;


    return app.exec();
}
