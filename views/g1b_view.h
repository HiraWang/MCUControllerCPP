#ifndef G1B_VIEW_H
#define G1B_VIEW_H

#include <QVBoxLayout>
#include <QWidget>

#include "../devices/device.h"
#include "../utility.h"
#include "../widgets/button.h"
#include "../widgets/canvas.h"
#include "../widgets/line_edit.h"

class G1BView : public QWidget {
  Q_OBJECT
  // enable meta object abilities

 public:
  G1BView(int w, int h, MetParaList* para_list, QWidget* parent = nullptr);
  virtual ~G1BView();
  SerialCode serial_status;
  DeviceG1B* g1b;

 private slots:
  void SetupUi();
  void SetSerialStatusOk();
  void SetSerialStatusFail();
  void ToggleFreqButton();
  void TogglePwButton();
  void ToggleVoltageButton();
  void ToggleOffsetButton();
  void ToggleOutButton();
  void ToggleImgButton();

 private:
  void Read();
  void Write();
  int w;
  int h;
  QVBoxLayout* layout;
  MetParaList* para_list;
  Helper* helper;
  MetCanvas* canvas;
  MetButton* freq_button;
  MetButton* pw_button;
  MetButton* voltage_button;
  MetButton* offset_button;
  MetButton* out_button;
  MetButton* img_button;
  MetButton* read_button;
  MetButton* write_button;
  MetLineEdit* freq_edit;
  MetLineEdit* pw_edit;
  MetLineEdit* voltage_edit;
  MetLineEdit* offset_edit;
};

#endif