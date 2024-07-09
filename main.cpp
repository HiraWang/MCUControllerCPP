#include <QApplication>
#include <QMainWindow>
#include <iostream>
using namespace std;

#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QFont font("Arial");
    app.setFont(font);

    MainWindow window;
    window.show();

    return app.exec();
}