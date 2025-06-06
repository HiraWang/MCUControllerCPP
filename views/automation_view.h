#ifndef AUTOMATION_H
#define AUTOMATION_H

#include <QLCDNumber>
#include <QProgressBar>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "../utility.h"
#include "../views/g1b_view.h"
#include "../views/monitor_view.h"
#include "../views/reglo_icc_view.h"
#include "../widgets/button.h"
#include "../widgets/canvas.h"
#include "../widgets/label.h"
#include "../widgets/line_edit.h"
#include "../widgets/menu.h"
#include "../widgets/process_unit.h"
#include "../widgets/text_edit.h"
#include "../widgets/tree.h"

struct MetTreeData {
  float value[2];
};

class TimerWorker : public QObject {
  Q_OBJECT
  // enable meta object abilities

 public:
  TimerWorker(QWidget* parent = nullptr);
  virtual ~TimerWorker();
  void Reset();

 signals:
  void TimeOut(int);

 public slots:
  void Start();
  void Finish();

 private:
  void Run();
  int count;
  QTimer* timer;
};

class AutomationView : public QWidget {
  Q_OBJECT  // enable meta object abilities

      public
      : AutomationView(int w, int h, DeviceG1B* g1b, DeviceRegloIcc* reglo_icc,
                       MonitorView* monitor_view, QWidget* parent = nullptr);
  virtual ~AutomationView();
  void ScaleUpSize();
  void ScaleDownSize();
  SerialCode serial_status;

 public slots:
  void Update(int);
  void UpdateUi();

 protected:
  void mousePressEvent(QMouseEvent* event);

 private slots:
  void ToggleRunButton();

 private:
  void InitLists();
  void Set();
  void SetupUi();
  void LoadStyleSheet();
  void RunProcess();
  void StopProcess();
  void StartPumpAllChannel();
  void StopPumpChannelNo2();
  void StartPulseGenerator();
  void StartPumpChannelNo2();
  void StopPulseGenerator();
  void StopPumpAllChannel();
  MetTreeData GetRpm();
  MetTreeData GetDir();
  MetTreeData GetFreq();
  MetTreeData GetPw();
  MetTreeData GetVoltage();
  MetTreeData GetOffset();
  int w;
  int h;
  int h_delta_1;
  int h_delta_2;
  int unit_cnt;
  int time_tot;
  QString style_sheet;
  QString style_sheet_lcd;
  QString style_sheet_status_on;
  QString style_sheet_status_off;
  DeviceG1B* g1b;
  DeviceRegloIcc* reglo_icc;
  QThread* thread;
  QTimer* ui_timer;
  TimerWorker* worker;
  QHBoxLayout* layout;
  MetProcessUnit** process_unit_list;
  MetProcessUnit* all_process;
  MetLabel* label_name;
  MetLabel* label_time;
  MetLabel* label_value;
  MetLabel* label_unit;
  MetLabel* label_status;
  QLCDNumber* lcd;
  QProgressBar* bar;
  MetTree* tree;
  MetTextEdit* text;
  MetCanvas* canvas;
  MetButton* button_run;
  MetParaList* para_list;
  MetMenu* menu;
  QWidget* container_automation;
  QWidget* container_left;
  QWidget* container_right;
  MonitorView* monitor_view;
  std::list<std::string> process_name_list;
  std::list<std::string> parameter_name_list;
  std::list<void (AutomationView::*)()> process_function_list;
  std::list<MetTreeData (AutomationView::*)()> parameter_function_list;
};

#endif