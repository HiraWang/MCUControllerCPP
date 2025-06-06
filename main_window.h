#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "main_window_ui.h"
#include "widgets/menu.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
  // enable meta object abilities

 public:
  // prohibit the implicit call of constructor
  // argument makes object have no parent QWidget
  explicit MainWindow(QWidget* parent = nullptr);
  virtual ~MainWindow();

 protected:
  void mousePressEvent(QMouseEvent* event);

 private slots:
  void ToggleExitButton();
  void ToggleWindowButton();
  void ToggleLoadConfigButton();
  void ToggleMenuButton();
  void ToggleConsoleButton();
  void ToggleConfigDirButton();
  void ToggleResultDirButton();
  void TogglePowerButton();
  void ToggleDeviceComboBox();

 private:
  // instance of class calls constructor in default
  QStringList device_list;
  QStringList mode_list;
  // pointer to class does not call constructor in default
  MetParaList* para_list;
  MainWindowUI* ui;
  MetMenu* menu;
};

class MainWindowController : public QObject {
  Q_OBJECT

 public:
  MainWindowController();
  ~MainWindowController();

 public slots:
  void Show();

 private:
  MainWindow* window;
};

#endif