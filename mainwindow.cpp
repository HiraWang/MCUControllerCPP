#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    Ui_MainWindow *ui = new Ui_MainWindow();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}