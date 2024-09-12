#include "main_window.h"

MainWindow::MainWindow(QWidget* parent) : 
    QMainWindow(parent), // call superclass constructor with an argument
    ui(new MainWindowUI())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}