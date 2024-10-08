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
    virtual ~MainWindow();

private slots:
    void ToggleExitButton();
    void ToggleWindowButton();
    void ToggleLoadConfigButton();
    void ToggleMenuButton();
    void ToggleUiTestButton();
    void TogglePowerButton();

private:
    // instance of class calls constructor in default
    QStringList device_list;
    // pointer to class does not call constructor in default
    MetParaList* para_list;
    MainWindowUI* ui;
};

#endif