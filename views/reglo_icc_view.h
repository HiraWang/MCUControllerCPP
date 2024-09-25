#ifndef REGLO_ICC_VIEW_H
#define REGLO_ICC_VIEW_H

#include <QHBoxLayout>
#include <QWidget>

#include "../utility.h"
#include "../devices/device.h"
#include "../widgets/buttons.h"

class RegloIccView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    RegloIccView(int w,
                 int h,
                 MetParaList* para_list,
                 QWidget* parent = nullptr);
    virtual ~RegloIccView();
    MetButton* read_button;
    MetButton* write_button;

private:
    void SetupUi();
    void Read();
    void Write();
    int w;
    int h;
    DeviceRegloIcc* reglo_icc;
    QHBoxLayout* layout;
    MetParaList* para_list;
};

#endif