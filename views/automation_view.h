#ifndef AUTOMATION_H
#define AUTOMATION_H

#include <QLCDNumber>
#include <QVBoxLayout>
#include <QWidget>

#include "../utility.h"
#include "../widgets/button.h"
#include "../widgets/label.h"
#include "../widgets/line_edit.h"
#include "../widgets/process_unit.h"

class AutomationView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    AutomationView(int w,
                   int h,
                   MetParaList* para_list,
                   QWidget* parent = nullptr);
    virtual ~AutomationView();

private:
    void SetupUi();
    void LoadStyleSheet();
    int w;
    int h;
    QString style_sheet;
    QString style_sheet_lcd;
    QString style_sheet_status_on;
    QString style_sheet_status_off;
    QVBoxLayout* layout;
    MetProcessUnit* process_unit_1;
    MetProcessUnit* process_unit_2;
    MetProcessUnit* process_unit_3;
    MetProcessUnit* process_unit_4;
    MetProcessUnit* process_unit_5;
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
};

#endif