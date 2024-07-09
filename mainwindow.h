#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#endif

#include <QMainWindow>
#include "mainwindow_ui.h"
class QWiddget;
class QHBoxLayout;
class UI_MainWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
    Ui_MainWindow* ui;
    QHBoxLayout* verticalLayout;
    QWidget* _widget1;
    QWidget* _widget2;
};