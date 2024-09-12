#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "main_window_ui.h"

class MainWindow : public QMainWindow
{  
    Q_OBJECT // enable meta object abilities

public:
    // prohibit the implicit call of constructor
    // argument makes object have no parent QWidget
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    MainWindowUI* ui;
};

#endif