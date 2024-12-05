#include <iostream>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "main_window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/QmlTest/main.qml"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    ListComPorts();

    QFont font("Arial");
    app.setFont(font);

    MainWindow window;
    window.show();

    return app.exec();
}