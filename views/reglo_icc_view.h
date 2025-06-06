#ifndef REGLO_ICC_VIEW_H
#define REGLO_ICC_VIEW_H

#include <QHBoxLayout>
#include <QWidget>

#include "../devices/device.h"
#include "../utility.h"
#include "../widgets/button.h"
#include "pump_channel_view.h"

class RegloIccView : public QWidget {
  Q_OBJECT
  // enable meta object abilities

 public:
  RegloIccView(int w, int h, MetParaList* para_list, QWidget* parent = nullptr);
  virtual ~RegloIccView();
  SerialCode serial_status;
  DeviceRegloIcc* reglo_icc;

 private:
  void SetupUi();
  void Read();
  void Write();
  int w;
  int h;
  QVBoxLayout* layout;
  MetParaList* para_list;
  MetPumpChannel* channel_1;
  MetPumpChannel* channel_2;
  MetButton* read_button;
  MetButton* write_button;
};

#endif