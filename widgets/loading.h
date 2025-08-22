#ifndef LOADING_H
#define LOADING_H

#include <QDialog>
#include <QString>
#include <QVBoxLayout>

#include "../devices/device.h"

class MetLoadingSubwindow : public QDialog {
  Q_OBJECT
  // enable meta object abilities

 public:
  MetLoadingSubwindow(QWidget* parent = nullptr);
  virtual ~MetLoadingSubwindow();

 private:
  void SetupUi();
  void LoadStyleSheet();
  QString style_sheet;
  QVBoxLayout* layout;
};

#endif