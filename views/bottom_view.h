#ifndef TAB_VIEW_H
#define TAB_VIEW_H

#include <QHBoxLayout>

#include "widgets/tab.h"

class BottomView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    BottomView(QWidget* parent = nullptr);
    ~BottomView();
    METTab* tab;

private:
    void setup_ui();
    QHBoxLayout* layout;
};

#endif