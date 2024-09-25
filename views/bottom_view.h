#ifndef TAB_VIEW_H
#define TAB_VIEW_H

#include <QHBoxLayout>

#include "../views/g1b_view.h"
#include "../widgets/tab.h"

class BottomView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    BottomView(QWidget* parent = nullptr);
    virtual ~BottomView();
    METTab* tab;
    G1BView* g1b_view;

private:
    void SetupUi();
    QHBoxLayout* layout;
};

#endif