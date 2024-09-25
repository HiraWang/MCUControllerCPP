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
                 METParaList* para_list,
                 QWidget* parent = nullptr);
    virtual ~RegloIccView();
    METButton* read_button;
    METButton* write_button;

private:
    void SetupUi();
    void Read();
    void Write();
    int w;
    int h;
    DeviceRegloIcc* reglo_icc;
    QHBoxLayout* layout;
    METParaList* para_list;
};

#endif