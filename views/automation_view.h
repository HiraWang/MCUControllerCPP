#ifndef AUTOMATION_H
#define AUTOMATION_H

#include <QLCDNumber>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "../utility.h"
#include "../views/g1b_view.h"
#include "../views/reglo_icc_view.h"
#include "../widgets/button.h"
#include "../widgets/label.h"
#include "../widgets/line_edit.h"
#include "../widgets/process_unit.h"

class TimerWorker : public QObject
{
    Q_OBJECT // enable meta object abilities

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

class AutomationView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    AutomationView(int w,
                   int h,
                   DeviceG1B* g1b,
                   DeviceRegloIcc* reglo_icc,
                   QWidget* parent = nullptr);
    virtual ~AutomationView();
    SerialCode serial_status;

public slots:
    void Update(int);

private slots:
    void ToggleSetButton();
    void ToggleRunButton();

private:
    void InitLists();
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
    int w;
    int h;
    int unit_cnt;
    int time_tot;
    QString style_sheet;
    QString style_sheet_lcd;
    QString style_sheet_status_on;
    QString style_sheet_status_off;
    DeviceG1B* g1b;
    DeviceRegloIcc* reglo_icc;
    QThread* thread;
    TimerWorker* worker;
    QVBoxLayout* layout;
    MetProcessUnit** process_unit_list;
    MetProcessUnit* all_process;
    MetLabel* label_name;
    MetLabel* label_time;
    MetLabel* label_value;
    MetLabel* label_unit;
    MetLabel* label_status;
    QLCDNumber* lcd;
    MetButton* button_set;
    MetButton* button_run;
    MetParaList* para_list;
    std::list<std::string> process_name_list;
    std::list<void (AutomationView::*)()> process_function_list;
};

#endif