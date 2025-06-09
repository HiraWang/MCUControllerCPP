#ifndef TAB_VIEW_H
#define TAB_VIEW_H

#include <QHBoxLayout>

#include "../views/automation_view.h"
#include "../views/monitor_view.h"
#include "../views/pulse_generator_view.h"
#include "../views/pump_view.h"
#include "../widgets/tab.h"

class BottomView : public QWidget {
  Q_OBJECT
  // enable meta object abilities

 public:
  BottomView(QWidget* parent = nullptr);
  virtual ~BottomView();
  MetTab* tab;
  AutomationView* automation_view;
  PulseGenView* pulse_gen_view;
  PumpView* pump_view;
  MonitorView* monitor_view;

 private:
  void SetupUi();
  QHBoxLayout* layout;
};

#endif