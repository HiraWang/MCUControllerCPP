#include <iostream>
#include <QApplication>

#include "main_window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ListComPorts();

    QFont font("Arial");
    app.setFont(font);

    MainWindow window;
    window.show();

    return app.exec();
}