#ifndef MONITOR_VIEW_H
#define MONITOR_VIEW_H

#include <QHBoxLayout>
#include <QWidget>

#include "../utility.h"
#include "../devices/device.h"
#include "../widgets/button.h"
#include "../widgets/canvas.h"

class MonitorView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    MonitorView(int w,
                int h,
                MetParaList* para_list,
                QWidget* parent = nullptr);
    virtual ~MonitorView();
    SerialCode serial_status;

private:
    void SetupUi();
    int w;
    int h;
    QVBoxLayout* layout;
    MetParaList* para_list;
    Helper* helper;
    MetCanvas* canvas;
};

#endif