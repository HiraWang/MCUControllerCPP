#include <iostream>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "main_window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QFont font("Arial");
    app.setFont(font);

    ListComPorts();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/QmlSource/splash_screen.qml"));
    QQmlComponent component(&engine, url);
    QObject* object = component.create();
    MainWindowController* example = new MainWindowController();
    QObject::connect(object, SIGNAL(qmlSignal()), example, SLOT(Show()));

    return app.exec();
}