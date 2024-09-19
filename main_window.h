﻿#ifndef MAIN_WINDOW_H
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

private slots:
    void toggle_exit_button();
    void toggle_window_button();
    void toggle_load_config_button();
    void toggle_menu_button();
    void toggle_power_button();

private:
    // instance of class calls constructor in default
    QStringList device_list;
    // pointer to class does not call constructor in default
    METParaList* para_list;
    MainWindowUI* ui;
};

#endif