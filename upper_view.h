#ifndef UPPER_VIEW_H
#define UPPER_VIEW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>

#include "widgets/buttons.h"

class UpperView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    UpperView(QWidget* parent = nullptr);
    ~UpperView();
    METButton* power_button;
    METButton* window_button;

private:
    void setup_ui();
    QHBoxLayout* layout;
};

#endif
