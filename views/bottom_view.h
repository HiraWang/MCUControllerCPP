#ifndef TAB_VIEW_H
#define TAB_VIEW_H

#include <QHBoxLayout>

#include "../utility.h"
#include "../widgets/tab.h"
#include "../views/g1b_view.h"

class BottomView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    BottomView(QWidget* parent = nullptr);
    virtual ~BottomView();
    METTab* tab;
    G1BView* g1b_view;

private:
    QHBoxLayout* layout;
    void setup_ui();
};

#endif