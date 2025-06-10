#include "pulse_generator_view.h"

#include <QTimer>

#include "../widgets/color.h"
#include "../widgets/label.h"
#include "../widgets/login_subwindow.h"
#include "../widgets/msg_subwindow.h"

extern int g_mode;

PulseGenView::PulseGenView(int w, int h, MetParaList* para_list,
                           QWidget* parent)
    : w(w),
      h(h),
      g1b(nullptr),
      due(nullptr),
      para_list(para_list),
      serial_status(SERIAL_OK),
      QWidget(parent) {
  if (g_mode == Mode::UI_TEST || g_mode == Mode::MONITOR_TEST) {
    serial_status = SERIAL_OK;
    SetupUi();
    return;
  }

  std::string str = para_list->list[PULSE_GEN_KEYWORD].str;
  std::wstring wstring = L"\\\\.\\" + std::wstring(str.begin(), str.end());
  LPCWSTR port = wstring.data();
  std::wcout << "PulseGenView:" << port << " " << sizeof(port) << '\n';

  if (para_list->list[PULSE_GEN_DEVICE].str == "G1B") {
    g1b = new DeviceG1B(port, CBR_1200, 8, ONESTOPBIT, NOPARITY);
    serial_status = g1b->Open();

    if (serial_status != SERIAL_OK) {
      MetMsgSubwindow("device G1B open failed");
      g1b = nullptr;
      return;
    } else {
      g_out << "device G1B opened" << '\n';
      QString account =
          QString::fromStdString(para_list->list[PULSE_GEN_ID].str);
      QString password =
          QString::fromStdString(para_list->list[PULSE_GEN_PASSWORD].str);
      MetLoginSubwindow(g1b, account, password, this);
    }
  } else if (para_list->list[PULSE_GEN_DEVICE].str == "DUE") {
    due = new DeviceArduinoDue(port, CBR_1200, 8, ONESTOPBIT, NOPARITY);
    serial_status = due->Open();

    if (serial_status != SERIAL_OK) {
      MetMsgSubwindow("device DUE open failed");
      due = nullptr;
      return;
    } else {
      g_out << "device DUE opened" << '\n';
      SetupUi();
    }
  } else {
    MetMsgSubwindow("invalid device");
    serial_status = SERIAL_FAIL;
    return;
  }
}

PulseGenView::~PulseGenView() {
  if (g1b && g1b->Close() != SERIAL_OK) {
    MetMsgSubwindow("device G1B close failed");
  }
}

void PulseGenView::SetupUi() {
  setFixedWidth(w);
  setFixedHeight(h);

  MetLabelStyle label_style;
  MetLabel* freq_label =
      new MetLabel(label_style, "Freq:", 200, WIDGET_H, this);
  MetLabel* pw_label =
      new MetLabel(label_style, "Pulse Width:", 200, WIDGET_H, this);
  MetLabel* voltage_label =
      new MetLabel(label_style, "Voltage:", 200, WIDGET_H, this);
  MetLabel* offset_label =
      new MetLabel(label_style, "Offset:", 200, WIDGET_H, this);
  MetLabel* out_label =
      new MetLabel(label_style, "Pulse State:", 200, WIDGET_H, this);

  MetLineEditStyle line_edit_style;
  freq_edit = new MetLineEdit(line_edit_style, 100, WIDGET_H, this);
  pw_edit = new MetLineEdit(line_edit_style, 100, WIDGET_H, this);
  voltage_edit = new MetLineEdit(line_edit_style, 100, WIDGET_H, this);
  offset_edit = new MetLineEdit(line_edit_style, 100, WIDGET_H, this);

  MetLabel* freq_unit = new MetLabel(label_style, "Hz", 120, WIDGET_H, this);
  MetLabel* pw_unit = new MetLabel(label_style, "us", 120, WIDGET_H, this);
  MetLabel* voltage_unit = new MetLabel(label_style, "V", 120, WIDGET_H, this);
  MetLabel* offset_unit = new MetLabel(label_style, "V", 120, WIDGET_H, this);

  MetButtonStyle button_style;
  freq_button = new MetButton(button_style, "SET", "SET", BUTTON_W, WIDGET_H,
                              "", "", this);
  pw_button = new MetButton(button_style, "SET", "SET", BUTTON_W, WIDGET_H, "",
                            "", this);
  voltage_button = new MetButton(button_style, "SET", "SET", BUTTON_W, WIDGET_H,
                                 "", "", this);
  offset_button = new MetButton(button_style, "SET", "SET", BUTTON_W, WIDGET_H,
                                "", "", this);
  img_button = new MetButton(button_style, "IMG", "IMG", BUTTON_W, WIDGET_H, "",
                             "", this);

  // status orientated button style
  MetButtonStyle two_state_button_style(COLOR_OFF_1, COLOR_ON_1, COLOR_OFF_2,
                                        COLOR_ON_2, COLOR_OFF_3, COLOR_ON_3);
  out_button = new MetButton(two_state_button_style, "", "", BUTTON_W, WIDGET_H,
                             "", "", this);

  connect(freq_button, &QPushButton::released, this,
          &PulseGenView::ToggleFreqButton);
  connect(pw_button, &QPushButton::released, this,
          &PulseGenView::TogglePwButton);
  connect(voltage_button, &QPushButton::released, this,
          &PulseGenView::ToggleVoltageButton);
  connect(offset_button, &QPushButton::released, this,
          &PulseGenView::ToggleOffsetButton);
  connect(out_button, &QPushButton::released, this,
          &PulseGenView::ToggleOutButton);
  connect(img_button, &QPushButton::released, this,
          &PulseGenView::ToggleImgButton);

  helper = new Helper(HelperType::PULSE_CHART);
  helper->SetPulseChartInfo(0, 0, 0, 0);
  canvas = new MetCanvas(helper, 200, 200, this);

  QWidget* space = new QWidget(this);
  space->setFixedWidth(20);

  QHBoxLayout* freq_layout = new QHBoxLayout();
  freq_layout->addWidget(freq_label, 0, Qt::AlignLeft);
  freq_layout->addWidget(freq_edit, 0, Qt::AlignCenter);
  freq_layout->addWidget(space, 0, Qt::AlignCenter);
  freq_layout->addWidget(freq_unit, 0, Qt::AlignLeft);
  freq_layout->addWidget(freq_button, 0, Qt::AlignRight);

  QHBoxLayout* pw_layout = new QHBoxLayout();
  pw_layout->addWidget(pw_label, 0, Qt::AlignLeft);
  pw_layout->addWidget(pw_edit, 0, Qt::AlignCenter);
  pw_layout->addWidget(space, 0, Qt::AlignCenter);
  pw_layout->addWidget(pw_unit, 0, Qt::AlignLeft);
  pw_layout->addWidget(pw_button, 0, Qt::AlignRight);

  QHBoxLayout* voltage_layout = new QHBoxLayout();
  voltage_layout->addWidget(voltage_label, 0, Qt::AlignLeft);
  voltage_layout->addWidget(voltage_edit, 0, Qt::AlignCenter);
  voltage_layout->addWidget(space, 0, Qt::AlignCenter);
  voltage_layout->addWidget(voltage_unit, 0, Qt::AlignLeft);
  voltage_layout->addWidget(voltage_button, 0, Qt::AlignRight);

  QHBoxLayout* offset_layout = new QHBoxLayout();
  offset_layout->addWidget(offset_label, 0, Qt::AlignLeft);
  offset_layout->addWidget(offset_edit, 0, Qt::AlignCenter);
  offset_layout->addWidget(space, 0, Qt::AlignCenter);
  offset_layout->addWidget(offset_unit, 0, Qt::AlignLeft);
  offset_layout->addWidget(offset_button, 0, Qt::AlignRight);

  QHBoxLayout* out_layout = new QHBoxLayout();
  out_layout->addWidget(out_label, 0, Qt::AlignLeft);
  out_layout->addWidget(out_button, 0, Qt::AlignRight);

  QWidget* container = new QWidget(this);
  container->setFixedWidth(700);
  container->setObjectName("g1b_container");
  container->setStyleSheet(
      "QWidget#g1b_container {"
      "background-color: " +
      QString(COLOR_GRAY) +
      ";"
      "border: 2px solid black;"
      "border-radius: 10px;"
      "}");
  QWidget* container_1 = new QWidget(this);
  QWidget* container_2 = new QWidget(this);
  QHBoxLayout* container_layout = new QHBoxLayout();
  QVBoxLayout* container_layout_1 = new QVBoxLayout();
  QVBoxLayout* container_layout_2 = new QVBoxLayout();

  container_layout_1->addItem(freq_layout);
  container_layout_1->addItem(pw_layout);
  container_layout_1->addItem(voltage_layout);
  container_layout_1->addItem(offset_layout);
  container_layout_1->addItem(out_layout);
  container_layout_1->addWidget(img_button, 0, Qt::AlignRight);
  container_layout_2->addWidget(canvas, 0, Qt::AlignCenter);
  container_1->setLayout(container_layout_1);
  container_2->setLayout(container_layout_2);
  container_layout->addWidget(container_1, 0, Qt::AlignCenter);
  container_layout->addWidget(container_2, 0, Qt::AlignCenter);
  container->setLayout(container_layout);

  layout = new QVBoxLayout(this);
  layout->addWidget(container, 0, Qt::AlignCenter);
  setLayout(layout);
}

void PulseGenView::SetSerialStatusOk() { serial_status = SERIAL_OK; }

void PulseGenView::SetSerialStatusFail() { serial_status = SERIAL_FAIL; }

void PulseGenView::ToggleFreqButton() {
  freq_button->SetButtonDefault();
  int freq = freq_edit->text().toInt();
  g1b->SetFreq(freq);
}

void PulseGenView::TogglePwButton() {
  pw_button->SetButtonDefault();
  float pw = pw_edit->text().toFloat();
  g1b->SetPulseWidth(pw);
}

void PulseGenView::ToggleVoltageButton() {
  voltage_button->SetButtonDefault();
  int voltage = voltage_edit->text().toInt();
  g1b->SetVoltage(voltage);
}

void PulseGenView::ToggleOffsetButton() {
  offset_button->SetButtonDefault();
  int offset = offset_edit->text().toInt();
  g1b->SetOffset(offset);
}

void PulseGenView::ToggleOutButton() {
  if (out_button->status) {
    out_button->SetButtonDefault();
    g1b->Off();
  } else {
    out_button->SetButtonPressed();
    g1b->On();
  }
}

void PulseGenView::ToggleImgButton() {
  if (freq_edit->text().isEmpty() || pw_edit->text().isEmpty() ||
      voltage_edit->text().isEmpty() || offset_edit->text().isEmpty()) {
    return;
  }
  int period = 1.0f / freq_edit->text().toFloat() * 1000000000.0f;
  int pulse_width = pw_edit->text().toFloat() * 1000.0f;
  int voltage = voltage_edit->text().toInt();
  int offset = offset_edit->text().toInt();
  helper->SetPulseChartInfo(period, pulse_width, voltage, offset);
  canvas->repaint();
}

void PulseGenView::Read() {
  if (g1b->Read() != SERIAL_OK) {
    MetMsgSubwindow("device G1B read failed");
  }
}

void PulseGenView::Write() {
  if (g1b->Write() != SERIAL_OK) {
    MetMsgSubwindow("device G1B write failed");
  }
}