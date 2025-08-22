#ifndef PUMP_CHANNEL_H
#define PUMP_CHANNEL_H

#include <QLabel>
#include <QString>
#include <QVBoxLayout>

#include "../devices/device.h"
#include "../widgets/button.h"
#include "../widgets/color.h"
#include "../widgets/font.h"
#include "../widgets/line_edit.h"

class MetPumpChannelStyle {
 public:
  MetPumpChannelStyle(QString bkg_color = COLOR_GRAY,
                      QString font_size = FONT_SIZE,
                      QString font_color = FONT_COLOR);
  virtual ~MetPumpChannelStyle();
  QString bkg_color;
  QString font_size;
  QString font_color;
};

class MetPumpChannel : public QWidget {
  Q_OBJECT
  // enable meta object abilities

 public:
  MetPumpChannel(MetPumpChannelStyle style, DeviceRegloIcc* reglo_icc,
                 BYTE channel, QString name, QWidget* parent = nullptr);
  virtual ~MetPumpChannel();
  MetLineEdit* rpm_edit;
  MetButton* rpm_button;
  MetButton* dir_button;
  MetButton* out_button;

 private slots:
  void ToggleRpmButton();
  void ToggleDirButton();
  void ToggleOutButton();

 private:
  void SetupUi();
  void LoadStyleSheet();
  void paintEvent(QPaintEvent* pe);
  BYTE channel;
  MetPumpChannelStyle met_style;
  QString style_sheet;
  QString style_sheet_lcd;
  QString style_sheet_dial;
  QString name;
  DeviceRegloIcc* reglo_icc;
  QVBoxLayout* layout;
};

#endif