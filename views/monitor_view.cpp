#include "monitor_view.h"

#include <direct.h>

#include <QGridLayout>

#include "../widgets/button.h"
#include "../widgets/login_subwindow.h"
#include "../widgets/msg_subwindow.h"

extern int g_mode;
extern MetMenu* g_menu;
extern std::string IMAGE_MET_LEFT;
extern std::string IMAGE_MET_RIGHT;
extern std::string IMAGE_MET_UP;
extern std::string IMAGE_MET_DOWN;
extern std::string IMAGE_MET_ATTACHED_FILES;
extern std::string IMAGE_MET_IMAGE;
extern std::string IMAGE_MET_LOAD;
extern std::string IMAGE_MET_MENU;
extern std::string IMAGE_MET_PROCESS;
extern std::string IMAGE_MET_RESULT;
extern std::string IMAGE_MET_SCAN;
extern std::string IMAGE_MET_STOP;
extern std::string IMAGE_MET_ZOOM_IN;
extern std::string IMAGE_MET_ZOOM_OUT;
extern std::string MONITOR_BUFFER_DIR;
extern std::string MONITOR_RESULT_DIR;

MonitorView::MonitorView(int w, int h, MetParaList* para_list, QWidget* parent)
    : w(w),
      h(h),
      call_analyze(false),
      scale_x_interval(0.5f),
      scale_y_interval(0.2f),
      due(nullptr),
      para_list(para_list),
      serial_status(SERIAL_OK),
      menu(nullptr),
      QWidget(parent) {
  if (g_mode == Mode::NORMAL || g_mode == Mode::UI_TEST) {
    serial_status = SERIAL_OK;
    SetupUi();
    return;
  }

  std::string str = para_list->list[MONITOR_KEYWORD].str;
  std::wstring wstring = L"\\\\.\\" + std::wstring(str.begin(), str.end());
  LPCWSTR port = wstring.data();
  std::wcout << "MonitorView:" << port << " " << sizeof(port) << '\n';

  due = new DeviceArduinoDue(port, CBR_9600, 8, ONESTOPBIT, NOPARITY);
  serial_status = due->Open();

  if (serial_status != SERIAL_OK) {
    MetMsgSubwindow("monitor open failed");
    due = nullptr;
    return;
  } else {
    g_out << "monitor opened" << '\n';
    due->activate = false;
    SetupUi();
  }
}

MonitorView::~MonitorView() {
  if (due && due->Close() != SERIAL_OK) {
    MetMsgSubwindow("device Due close failed");
  }
}

void MonitorView::SetupUi() {
  setFixedWidth(w);
  setFixedHeight(h);

  helper = new Helper(HelperType::OSCILLOSCOPE);
  helper->InitOscilloscopeInfo(para_list->list[OFFSET].num, 1000.0f, 0.0f);
  canvas = new MetCanvas(helper, width() - 25, height() - 125, this);
  canvas->setContentsMargins(0, 0, 0, 0);

  timer = new QElapsedTimer();
  ui_timer = new QTimer(this);
  connect(ui_timer, &QTimer::timeout, this, &MonitorView::Update);

  MetButtonStyle button_style;
  scan_button =
      new MetButton(button_style, "scan", "stop", BUTTON_W, BUTTON_W,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_SCAN)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_STOP)), this);
  scale_reset_button =
      new MetButton(button_style, "reset", "", WIDGET_H, WIDGET_H,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)), this);
  scale_x_plus_button =
      new MetButton(button_style, "x zoom in", "", WIDGET_H, WIDGET_H,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_RIGHT)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_RIGHT)), this);
  scale_y_plus_button =
      new MetButton(button_style, "y zoom in", "", WIDGET_H, WIDGET_H,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_UP)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_UP)), this);
  scale_x_minus_button =
      new MetButton(button_style, "x zoom out", "", WIDGET_H, WIDGET_H,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_LEFT)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_LEFT)), this);
  scale_y_minus_button =
      new MetButton(button_style, "y zoom out", "", WIDGET_H, WIDGET_H,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_DOWN)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_DOWN)), this);
  plot_info_button = new MetButton(
      button_style, "hide plot info", "show plot info", BUTTON_W, BUTTON_W,
      QString::fromStdString(GetAbsPath(IMAGE_MET_MENU)),
      QString::fromStdString(GetAbsPath(IMAGE_MET_MENU)), this);
  render_button =
      new MetButton(button_style, "render", "", BUTTON_W, BUTTON_W,
                    QString::fromStdString(GetAbsPath(IMAGE_MET_IMAGE)),
                    QString::fromStdString(GetAbsPath(IMAGE_MET_IMAGE)), this);
  analyze_button = new MetButton(
      button_style, "calculate frequency", "", BUTTON_W, BUTTON_W,
      QString::fromStdString(GetAbsPath(IMAGE_MET_PROCESS)),
      QString::fromStdString(GetAbsPath(IMAGE_MET_PROCESS)), this);
  buffer_dir_button = new MetButton(
      button_style, "open buffer directory", "", BUTTON_W, BUTTON_W,
      QString::fromStdString(GetAbsPath(IMAGE_MET_ATTACHED_FILES)),
      QString::fromStdString(GetAbsPath(IMAGE_MET_ATTACHED_FILES)), this);
  result_dir_button = new MetButton(
      button_style, "open result directory", "", BUTTON_W, BUTTON_W,
      QString::fromStdString(GetAbsPath(IMAGE_MET_RESULT)),
      QString::fromStdString(GetAbsPath(IMAGE_MET_RESULT)), this);

  connect(scan_button, &QPushButton::released, this,
          &MonitorView::ToggleScanButton);
  connect(scale_reset_button, &QPushButton::released, this,
          &MonitorView::ToggleScaleResetButton);
  connect(scale_x_plus_button, &QPushButton::released, this,
          &MonitorView::ToggleScaleXPlusButton);
  connect(scale_y_plus_button, &QPushButton::released, this,
          &MonitorView::ToggleScaleYPlusButton);
  connect(scale_x_minus_button, &QPushButton::released, this,
          &MonitorView::ToggleScaleXMinusButton);
  connect(scale_y_minus_button, &QPushButton::released, this,
          &MonitorView::ToggleScaleYMinusButton);
  connect(plot_info_button, &QPushButton::released, this,
          &MonitorView::TogglePlotInfoButton);
  connect(render_button, &QPushButton::released, this,
          &MonitorView::ToggleRenderButton);
  connect(analyze_button, &QPushButton::released, this,
          &MonitorView::ToggleAnalyzeButton);
  connect(buffer_dir_button, &QPushButton::released, this,
          &MonitorView::ToggleBufferDirButton);
  connect(result_dir_button, &QPushButton::released, this,
          &MonitorView::ToggleResultDirButton);

  MetSliderStyle slider_style(COLOR_WHITE, COLOR_BLACK);
  data_offset_slider =
      new MetSlider(slider_style, Qt::Vertical, 10, 76, 0, 24, 1, this);
  data_offset_slider->setValue(para_list->list[OFFSET].num);
  data_offset_slider->setSliderPosition(para_list->list[OFFSET].num);

  connect(data_offset_slider, &QSlider::valueChanged, this,
          &MonitorView::ToggleDataOffsetSlider);

  MetLcdStyle lcd_style(COLOR_BLACK, "rgb(113, 113, 113)", COLOR_WHITE,
                        FONT_SIZE);
  timer_lcd = new MetLcd(lcd_style, "Time", "s", 60, 35, 120, 35, this);
  signal_lcd = new MetLcd(lcd_style, "Count", "M", 60, 35, 120, 35, this);

  QWidget* scale_buttons = new QWidget(this);
  scale_buttons->setFixedWidth(100);
  scale_buttons->setFixedHeight(100);
  QGridLayout* scale_layout = new QGridLayout();
  scale_layout->addWidget(scale_x_minus_button, 1, 0, Qt::AlignCenter);
  scale_layout->addWidget(scale_x_plus_button, 1, 2, Qt::AlignCenter);
  scale_layout->addWidget(scale_reset_button, 1, 1, Qt::AlignCenter);
  scale_layout->addWidget(scale_y_minus_button, 2, 1, Qt::AlignCenter);
  scale_layout->addWidget(scale_y_plus_button, 0, 1, Qt::AlignCenter);
  scale_layout->setContentsMargins(11, 9, 11, 11);
  scale_buttons->setLayout(scale_layout);

  QWidget* lcds = new QWidget(this);
  lcds->setFixedWidth(180);
  lcds->setFixedHeight(100);
  QVBoxLayout* lcd_layout = new QVBoxLayout();
  lcd_layout->addWidget(timer_lcd, 0, {Qt::AlignRight, Qt::AlignTop});
  lcd_layout->addWidget(signal_lcd, 0, {Qt::AlignRight, Qt::AlignTop});
  lcd_layout->setContentsMargins(0, 11, 0, 11);
  lcds->setLayout(lcd_layout);

  QWidget* upper_widgets = new QWidget(this);
  QHBoxLayout* upper_layout = new QHBoxLayout();
  upper_layout->addWidget(scan_button, 0, Qt::AlignLeft);
  upper_layout->addWidget(plot_info_button, 0, Qt::AlignLeft);
  upper_layout->addWidget(render_button, 0, Qt::AlignLeft);
  upper_layout->addWidget(analyze_button, 0, Qt::AlignLeft);
  upper_layout->addWidget(buffer_dir_button, 0, Qt::AlignLeft);
  upper_layout->addWidget(result_dir_button, 0, Qt::AlignLeft);
  upper_layout->addWidget(data_offset_slider, 0, Qt::AlignLeft);
  upper_layout->addWidget(scale_buttons, 0, Qt::AlignLeft);
  upper_layout->addStretch(10);
  upper_layout->addWidget(lcds, 0, Qt::AlignRight);
  upper_layout->setContentsMargins(0, 0, 0, 0);
  upper_widgets->setLayout(upper_layout);

  layout = new QVBoxLayout(this);
  layout->setContentsMargins(15, 15, 15, 15);
  layout->addWidget(upper_widgets, 0, Qt::AlignTop);
  layout->addWidget(canvas, 0, {Qt::AlignHCenter, Qt::AlignBottom});
  layout->addStretch(1);
  setLayout(layout);
}

void MonitorView::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::RightButton) {
    if (g_menu) g_menu->close();

    menu = new MetMenu();

    QAction* act_show_count = menu->addAction("Show count");
    connect(act_show_count, &QAction::triggered, this, [=]() {
      QString msg;
      if (due) {
        msg = "Current count is " + QString::number(due->count);
      } else {
        msg = "No device detected";
      }
      MetMsgSubwindow(msg, MSG_INFO, menu);
      menu->close();
      menu = nullptr;
    });

    menu->addSeparator();

    QIcon icon_zoom_in =
        QIcon(QString::fromStdString(GetAbsPath(IMAGE_MET_ZOOM_IN)));
    QAction* act_zoom_in = menu->addAction(icon_zoom_in, "Zoom in");
    connect(act_zoom_in, &QAction::triggered, this, [=]() {
      ToggleScaleXPlusButton();
      ToggleScaleYPlusButton();
    });

    QIcon icon_zoom_out =
        QIcon(QString::fromStdString(GetAbsPath(IMAGE_MET_ZOOM_OUT)));
    QAction* act_zoom_out = menu->addAction(icon_zoom_out, "Zoom out");
    connect(act_zoom_out, &QAction::triggered, this, [=]() {
      ToggleScaleXMinusButton();
      ToggleScaleYMinusButton();
    });

    menu->addSeparator();

    QIcon icon_render =
        QIcon(QString::fromStdString(GetAbsPath(IMAGE_MET_IMAGE)));
    QAction* act_render = menu->addAction(icon_render, "Screen shot");
    connect(act_render, &QAction::triggered, this, [=]() {
      ToggleRenderButton();
      menu->close();
      menu = nullptr;
    });

    menu->exec(QCursor::pos());
  } else if (event->button() == Qt::LeftButton) {
    if (menu) {
      QAction* action = menu->actionAt(event->pos());
      if (!action) {
        menu->close();
        menu = nullptr;
      }
    }
  }
}

void MonitorView::Update() {
  size_t elapsed_time_ms = static_cast<size_t>(timer->elapsed());
  size_t elapsed_time = elapsed_time_ms / 1000;
  size_t minute = elapsed_time / 60;
  size_t second = elapsed_time % 60;
  timer_lcd->display(QString::number(minute) + ":" + QString::number(second));

  size_t count = due->count;
  size_t signal_count = count * MONITOR_BUFFER_SIZE;
  size_t signal_count_m = signal_count / 1000000;
  signal_lcd->display(QString::number(signal_count_m));

  helper->SetCount(count);
  canvas->update();

  if (call_analyze) {
    std::thread* t = new std::thread(&Helper::AnalyzeData, helper, count - 1);
    call_analyze = false;
  }
}

void MonitorView::ScaleUpCanvasSize() {
  canvas->setFixedHeight(height());
  canvas->update();
}

void MonitorView::ScaleDownCanvasSize() {
  canvas->setFixedHeight(height() - 145);
  canvas->update();
}

void MonitorView::ToggleScanButton() {
  if (scan_button->status) {
    scan_button->SetButtonDefault();
    due->activate = false;
    due->count = 0;
    thread->join();
    ui_timer->stop();
  } else {
    scan_button->SetButtonPressed();
    // initialization
    // initialize result directory
    _mkdir(MONITOR_RESULT_DIR.c_str());
    RemoveAllFilesFromDir(MONITOR_RESULT_DIR.c_str());
    // initialize helper
    helper->SetDataMinAndMax(1000.0f, 0.0f);
    helper->SetFirstRoundFlag(true);
    // initialize device
    due->activate = true;
    due->count = 0;
    // activation
    // start reading buffer
    thread = new std::thread(&DeviceArduinoDue::ReadBufferAndSave, due);
    Sleep(1000);
    // start calculating elapsed time
    timer->start();
    // start refreshing UI
    ui_timer->start(10);
  }
}

void MonitorView::ToggleScaleResetButton() {
  scale_reset_button->SetButtonDefault();
  helper->SetScaleX(1.0f);
  helper->SetScaleY(1.0f);
  canvas->update();
}

void MonitorView::ToggleScaleXPlusButton() {
  scale_x_plus_button->SetButtonDefault();
  float scale_x = helper->GetScaleX();
  scale_x += scale_x_interval;

  if (1.0f <= scale_x && scale_x < 10.0f) {
    helper->SetScaleX(scale_x);
    canvas->update();
  }
}

void MonitorView::ToggleScaleYPlusButton() {
  scale_y_plus_button->SetButtonDefault();
  float scale_y = helper->GetScaleY();
  scale_y += scale_y_interval;

  if (0.0f < scale_y && scale_y < 100.0f) {
    helper->SetScaleY(scale_y);
    canvas->update();
  }
}

void MonitorView::ToggleScaleXMinusButton() {
  scale_x_plus_button->SetButtonDefault();
  float scale_x = helper->GetScaleX();
  scale_x -= scale_x_interval;

  if (1.0f <= scale_x && scale_x < 10.0f) {
    helper->SetScaleX(scale_x);
    canvas->update();
  }
}

void MonitorView::ToggleScaleYMinusButton() {
  scale_y_plus_button->SetButtonDefault();
  float scale_y = helper->GetScaleY();
  scale_y -= scale_y_interval;

  if (scale_y_interval <= scale_y && scale_y < 100.0f) {
    helper->SetScaleY(scale_y);
    canvas->update();
  }
}

void MonitorView::TogglePlotInfoButton() {
  if (plot_info_button->status) {
    plot_info_button->SetButtonDefault();
    helper->SetPlotInfoFlag(true);
  } else {
    plot_info_button->SetButtonPressed();
    helper->SetPlotInfoFlag(false);
  }
}

void MonitorView::ToggleRenderButton() {
  render_button->SetButtonDefault();
  canvas->SetRenderFlag(true);
}

void MonitorView::ToggleAnalyzeButton() {
  analyze_button->SetButtonDefault();
  call_analyze = true;
}

void MonitorView::ToggleBufferDirButton() {
  buffer_dir_button->SetButtonDefault();
  std::wstring result_dir =
      std::wstring(MONITOR_BUFFER_DIR.begin(), MONITOR_BUFFER_DIR.end());
  ShellExecute(nullptr, L"open", nullptr, nullptr, result_dir.c_str(),
               SW_SHOWNORMAL);
}

void MonitorView::ToggleResultDirButton() {
  buffer_dir_button->SetButtonDefault();
  std::wstring result_dir =
      std::wstring(MONITOR_RESULT_DIR.begin(), MONITOR_RESULT_DIR.end());
  ShellExecute(nullptr, L"open", nullptr, nullptr, result_dir.c_str(),
               SW_SHOWNORMAL);
}

void MonitorView::ToggleDataOffsetSlider() {
  if (data_offset_slider->value() == 0) {
    helper->SetDataOffset(1);
  } else {
    helper->SetDataOffset(data_offset_slider->value());
  }
}