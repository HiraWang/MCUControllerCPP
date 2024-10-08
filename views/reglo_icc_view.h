#ifndef REGLO_ICC_VIEW_H
#define REGLO_ICC_VIEW_H

#include <QHBoxLayout>
#include <QWidget>

#include "pump_channel_view.h"
#include "../utility.h"
#include "../devices/device.h"
#include "../widgets/button.h"

class RegloIccView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    RegloIccView(int w,
                 int h,
                 MetParaList* para_list,
                 QWidget* parent = nullptr);
    virtual ~RegloIccView();
    MetPumpChannel* channel_1;
    MetPumpChannel* channel_2;
    MetButton* read_button;
    MetButton* write_button;
    DeviceRegloIcc* reglo_icc;
    SerialCode serial_status;

private:
    void SetupUi();
    void Read();
    void Write();
    int w;
    int h;
    QVBoxLayout* layout;
    MetParaList* para_list;
};

#endif