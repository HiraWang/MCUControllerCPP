#include <iostream>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include "main_window.h"
#include "test.h"

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
    HWND h_window = GetConsoleWindow();
    HMENU h_menu = GetSystemMenu(h_window, FALSE);
    EnableMenuItem(h_menu, SC_CLOSE, MF_GRAYED);
    GetConsoleMode(handle, &prev_mode);
    SetConsoleMode(handle, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
    SetConsoleTitle(L"Debug Console");

    // Construct Qml engine and splash screen
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/QmlSource/splash_screen.qml"));
    QQmlComponent component(&engine, url);
    QObject* object = component.create();
    MainWindowController* controller = new MainWindowController();
    QObject::connect(object, SIGNAL(qmlLoaderFinish()), controller, SLOT(Show()));

    MyClass mine;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("myClass", &mine);
    engine.load(QStringLiteral("qrc:/QmlSource/test.qml"));
    mine.test();

    return app.exec();
}