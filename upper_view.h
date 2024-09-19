#ifndef UPPER_VIEW_H
#define UPPER_VIEW_H

#include <QPushButton>
#include <QHBoxLayout>

#include "widgets/buttons.h"
#include "widgets/combo_box.h"
#include "widgets/label.h"
#include "widgets/menu.h"

class UpperView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    UpperView(QWidget* parent = nullptr);
    ~UpperView();
    METMenu* menu;
    METButton* exit_button;
    METButton* window_button;
    METButton* load_config_button;
    METButton* menu_button;
    METButton* power_button;
    METComboBox* combo_box;

private:
    void setup_ui();
    METLabel* label;
    QHBoxLayout* layout;
};

#endif
