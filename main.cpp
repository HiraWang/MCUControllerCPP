#include <QApplication>
#include <QMainWindow>
#include <iostream>
using namespace std;

#include "main_window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // set default font
    QFont font("Arial");
    app.setFont(font);

    MainWindow window;
    window.show();

    return app.exec();
}