#include "upper_view.h"

extern std::string IMAGE_MET_CLOSE;
extern std::string IMAGE_MET_CONSOLE;
extern std::string IMAGE_MET_EXIT;
extern std::string IMAGE_MET_FULL_SCREEN;
extern std::string IMAGE_MET_LOAD;
extern std::string IMAGE_MET_MAX_SIZE;
extern std::string IMAGE_MET_MENU;
extern std::string IMAGE_MET_POWER;
extern std::string IMAGE_MET_RESULT;

UpperView::UpperView(QWidget* parent) : QWidget(parent) { SetupUi(); }

UpperView::~UpperView() {}

void UpperView::SetupUi() {
  MetLabelStyle label_style(COLOR_DEEP_GRAY, FONT_SIZE, COLOR_LIGHT_GRAY);
  device_label = new MetLabel(label_style, "Device", 60, WIDGET_H, this);
  mode_label = new MetLabel(label_style, "Mode", 60, WIDGET_H, this);

  MetComboBoxStyle combo_box_style;
  device_combo_box = new MetComboBox(combo_box_style, 250, 20, this);
  mode_combo_box = new MetComboBox(combo_box_style, 250, 20, this);

  // process orientated button style
  MetButtonStyle button_style;
  exit_button =
      new MetButton(button_style, "exit program", "", BUTTON_W, BUTTON_W,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_EXIT)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_EXIT)), this);
  window_button = new MetButton(
      button_style, "maximize window", "fullscreen", BUTTON_W, BUTTON_W,
      QString::fromStdString(GetAbsPath(IMAGE_MET_MAX_SIZE)),
      QString::fromStdString(GetAbsPath(IMAGE_MET_FULL_SCREEN)), this);
  load_config_button =
      new MetButton(button_style, "load config", "", BUTTON_W, BUTTON_W,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)), this);
  menu_button =
      new MetButton(button_style, "show menu", "close menu", BUTTON_W, BUTTON_W,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_MENU)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_CLOSE)), this);
  console_button = new MetButton(
      button_style, "show console", "close console", BUTTON_W, BUTTON_W,
      QString::fromStdString(GetAbsPath(IMAGE_MET_CONSOLE)),
      QString::fromStdString(GetAbsPath(IMAGE_MET_CLOSE)), this);
  result_dir_button = new MetButton(
      button_style, "open result directory", "", BUTTON_W, BUTTON_W,
      QString::fromStdString(GetAbsPath(IMAGE_MET_RESULT)),
      QString::fromStdString(GetAbsPath(IMAGE_MET_RESULT)), this);

  MetButtonStyle power_button_style(COLOR_OFF_1, COLOR_ON_1, COLOR_OFF_2,
                                    COLOR_ON_2, COLOR_OFF_3, COLOR_ON_3);
  power_button = new MetButton(
      power_button_style, "power on", "power off", BUTTON_W, BUTTON_W,
      QString::fromStdString(GetAbsPath(IMAGE_MET_POWER)),
      QString::fromStdString(GetAbsPath(IMAGE_MET_POWER)), this);

  QWidget* container_combo_box = new QWidget(this);
  QVBoxLayout* layout_combo_box = new QVBoxLayout();
  QHBoxLayout* layout_device_combo_box = new QHBoxLayout();
  QHBoxLayout* layout_mode_combo_box = new QHBoxLayout();

  layout_device_combo_box->addWidget(device_label, 0,
                                     Qt::AlignTop | Qt::AlignLeft);
  layout_device_combo_box->addWidget(device_combo_box, 0,
                                     Qt::AlignTop | Qt::AlignLeft);
  layout_mode_combo_box->addWidget(mode_label, 0,
                                   Qt::AlignBottom | Qt::AlignLeft);
  layout_mode_combo_box->addWidget(mode_combo_box, 0,
                                   Qt::AlignBottom | Qt::AlignLeft);
  layout_combo_box->addItem(layout_device_combo_box);
  layout_combo_box->addItem(layout_mode_combo_box);
  container_combo_box->setLayout(layout_combo_box);

  layout = new QHBoxLayout(this);
  layout->addWidget(container_combo_box, 0, Qt::AlignTop | Qt::AlignLeft);
  layout->addStretch(10);
  layout->addWidget(exit_button, 0, Qt::AlignTop | Qt::AlignRight);
  layout->addWidget(window_button, 0, Qt::AlignTop | Qt::AlignRight);
  layout->addWidget(load_config_button, 0, Qt::AlignTop | Qt::AlignRight);
  layout->addWidget(menu_button, 0, Qt::AlignTop | Qt::AlignRight);
  layout->addWidget(console_button, 0, Qt::AlignTop | Qt::AlignRight);
  layout->addWidget(result_dir_button, 0, Qt::AlignTop | Qt::AlignRight);
  layout->addWidget(power_button, 0, Qt::AlignTop | Qt::AlignRight);
  setLayout(layout);
}