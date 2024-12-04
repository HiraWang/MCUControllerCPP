#ifndef UPPER_VIEW_H
#define UPPER_VIEW_H

#include <QHBoxLayout>
#include <QPushButton>

#include "../utility.h"
#include "../widgets/button.h"
#include "../widgets/combo_box.h"
#include "../widgets/dialog.h"
#include "../widgets/label.h"

class UpperView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    UpperView(QWidget* parent = nullptr);
    virtual ~UpperView();
    MetDialog* menu;
    MetComboBox* device_combo_box;
    MetComboBox* mode_combo_box;
    MetButton* exit_button;
    MetButton* window_button;
    MetButton* load_config_button;
    MetButton* menu_button;
    MetButton* console_button;
    MetButton* result_dir_button;
    MetButton* power_button;

private:
    void SetupUi();
    MetLabel* device_label;
    MetLabel* mode_label;
    QHBoxLayout* layout;
};

#endif
