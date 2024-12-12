#include <iostream>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "main_window.h"

int main(int argc, char* argv[]) {
    // Construct Qt Application
    QApplication app(argc, argv);
    QFont font("Arial");
    app.setFont(font);

    ListComPorts();
    
    // Optimize console
    ResizeConsole(1520, 680);
    DWORD prev_mode;
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(handle, &prev_mode);
    SetConsoleMode(handle, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

    // Construct Qml engine and splash screen
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/QmlSource/splash_screen.qml"));
    QQmlComponent component(&engine, url);
    QObject* object = component.create();
    MainWindowController* controller = new MainWindowController();
    QObject::connect(object, SIGNAL(qmlLoaderFinish()), controller, SLOT(Show()));

    return app.exec();
}