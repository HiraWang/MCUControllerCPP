#ifndef UPPER_VIEW_H
#define UPPER_VIEW_H

#include <QPushButton>
#include <QHBoxLayout>
#include "widgets/buttons.h"

class UpperView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    UpperView(QWidget* parent = nullptr);
    ~UpperView();

private:
    void setup_ui();
    void paintEvent(QPaintEvent* pe);
    QHBoxLayout* layout;
    METButton* power_button;
    METButton* window_button;
};

#endif
