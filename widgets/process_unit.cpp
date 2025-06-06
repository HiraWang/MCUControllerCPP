#include "process_unit.h"

#include "utility.h"

extern std::string IMAGE_MET_MINUS;
extern std::string IMAGE_MET_PLUS;

MetProcessUnit::MetProcessUnit(MetProcessUnitStyle style, int id, QString name,
                               QString time, bool is_normal_unit,
                               QWidget* parent)
    : style(style),
      id(id),
      time(0),
      time_tot(0),
      is_normal_unit(is_normal_unit),
      QWidget(parent) {
  setFixedWidth(700);
  LoadStyleSheet();

  MetLabelStyle label_style_1(COLOR_BLACK, FONT_SIZE, COLOR_WHITE);
  label_name = new MetLabel(label_style_1, name, 225, WIDGET_H, this);
  label_name->setObjectName("process_name");
  label_name->setStyleSheet(
      "QLabel#process_name {"
      "background-color: " +
      QString(COLOR_DEEP_GRAY) +
      ";"
      "border-radius: 5px;"
      "padding-left: 2px;"
      "font: bold " +
      QString(FONT_SIZE) +
      ";"
      "color: " +
      QString(COLOR_WHITE) +
      ";"
      "}");

  MetLabelStyle label_style_2;
  label_time = new MetLabel(label_style_2, time, 120, WIDGET_H, this);
  label_unit = new MetLabel(label_style_2, "s", 20, WIDGET_H, this);
  label_status = new MetLabel(label_style_2, "", WIDGET_H, WIDGET_H, this);

  MetLineEditStyle line_edit_style;
  time_edit = new MetLineEdit(line_edit_style, 100, WIDGET_H, this);

  MetButtonStyle button_style;
  button_minus_one =
      new MetButton(button_style, "minus", "", WIDGET_H, WIDGET_H,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_MINUS)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_MINUS)), this);
  button_plus_one =
      new MetButton(button_style, "plus", "", WIDGET_H, WIDGET_H,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_PLUS)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_PLUS)), this);

  if (is_normal_unit) {
    connect(button_minus_one, &QPushButton::released, this,
            &MetProcessUnit::ToggleMinusOneButton);
    connect(button_plus_one, &QPushButton::released, this,
            &MetProcessUnit::TogglePlusOneButton);
  } else {
    button_minus_one->setEnabled(false);
    button_minus_one->setIcon(QIcon());
    button_minus_one->setStyleSheet(
        "background-color: transparent;"
        "border-radius: 0px;");
    button_plus_one->setEnabled(false);
    button_plus_one->setIcon(QIcon());
    button_plus_one->setStyleSheet(
        "background-color: transparent;"
        "border-radius: 0px;");
  }

  lcd = new QLCDNumber();
  lcd->setFixedWidth(BUTTON_W);
  lcd->setFixedHeight(WIDGET_H);
  lcd->setStyleSheet(style_sheet_lcd);
  lcd->display(0);

  status = false;
  label_status->setStyleSheet(style_sheet_status_off);

  layout = new QHBoxLayout(this);
  layout->addWidget(label_name, 0, Qt::AlignLeft);
  layout->addWidget(label_time, 0, Qt::AlignCenter);
  layout->addWidget(time_edit, 0, Qt::AlignCenter);
  layout->addWidget(label_unit, 0, Qt::AlignCenter);
  layout->addWidget(button_minus_one, 0, Qt::AlignCenter);
  layout->addWidget(button_plus_one, 0, Qt::AlignCenter);
  layout->addWidget(lcd, 0, Qt::AlignCenter);
  layout->addWidget(label_status, 0, Qt::AlignRight);
  setLayout(layout);
}

MetProcessUnit::~MetProcessUnit() {}

void MetProcessUnit::LoadStyleSheet() {
  style_sheet_lcd =
      "QLCDNumber {"
      "background-color: " +
      style.bkg_color +
      ";"
      "border: 2px solid rgb(113, 113, 113);"
      "border-width: 3px;"
      "border-radius: 5px;"
      "color: " +
      style.font_color +
      ";"
      "font: " +
      style.font_size +
      ";"
      "}";
  style_sheet_status_on = "background-color: " + style.color_1 +
                          ";"
                          "border-radius: 2px;";
  style_sheet_status_off = "background-color: " + style.color_2 +
                           ";"
                           "border-radius: 2px;";
}

void MetProcessUnit::ToggleMinusOneButton() {
  time = time_edit->text().toInt();
  time_edit->setText(QString::number(--time));
}

void MetProcessUnit::TogglePlusOneButton() {
  time = time_edit->text().toInt();
  time_edit->setText(QString::number(++time));
}

void MetProcessUnit::StatusOn() {
  if (status == false) {
    label_status->setStyleSheet(style_sheet_status_on);
    status = true;
  }
}

void MetProcessUnit::StatusOff() {
  label_status->setStyleSheet(style_sheet_status_off);
  status = false;
}

void MetProcessUnit::SetLcd(QString num) { lcd->display(num); }

MetProcessUnitStyle::MetProcessUnitStyle(QString bkg_color, QString color_1,
                                         QString color_2, QString font_size,
                                         QString font_color)
    : bkg_color(bkg_color),
      color_1(color_1),
      color_2(color_2),
      font_size(font_size),
      font_color(font_color) {}

MetProcessUnitStyle::~MetProcessUnitStyle() {}