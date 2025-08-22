#ifndef PROCESS_UNIT_H
#define PROCESS_UNIT_H

#include <QHBoxLayout>
#include <QLCDNumber>
#include <QString>
#include <QWidget>

#include "button.h"
#include "color.h"
#include "font.h"
#include "label.h"
#include "line_edit.h"

class MetProcessUnitStyle {
 public:
  MetProcessUnitStyle(QString bkg_color = COLOR_BLACK,
                      QString color_1 = COLOR_ON_1,
                      QString color_2 = COLOR_OFF_1,
                      QString font_size = FONT_SIZE,
                      QString font_color = COLOR_WHITE);
  virtual ~MetProcessUnitStyle();
  QString bkg_color;
  QString color_1;
  QString color_2;
  QString font_size;
  QString font_color;
};

class MetProcessUnit : public QWidget {
  Q_OBJECT
  // enable meta object abilities

 public:
  MetProcessUnit(MetProcessUnitStyle style, int id, QString name, QString time,
                 bool is_normal_unit = true, QWidget* parent = nullptr);
  virtual ~MetProcessUnit();
  void StatusOn();
  void StatusOff();
  void SetLcd(QString num);
  bool is_normal_unit;
  bool status;
  int id;
  int time;
  int time_tot;
  MetLabel* label_name;
  MetLineEdit* time_edit;
  MetButton* button_plus_one;
  MetButton* button_minus_one;

 private slots:
  void ToggleMinusOneButton();
  void TogglePlusOneButton();

 private:
  void LoadStyleSheet();
  MetProcessUnitStyle style;
  QString style_sheet_lcd;
  QString style_sheet_status_on;
  QString style_sheet_status_off;
  QHBoxLayout* layout;
  MetLabel* label_time;
  MetLabel* label_unit;
  MetLabel* label_status;
  QLCDNumber* lcd;
};

#endif