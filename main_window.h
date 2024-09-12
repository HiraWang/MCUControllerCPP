#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#endif

#include <QMainWindow>
#include "main_window_ui.h"

class QWiddget;
class QHBoxLayout;
class UI_MainWindow;
  
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
    QHBoxLayout* layout;
    QWidget* _widget1;
    QWidget* _widget2;
};