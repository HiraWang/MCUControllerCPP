#ifndef MONITOR_VIEW_H
#define MONITOR_VIEW_H

#include <QHBoxLayout>
#include <QWidget>
#include <QTimer>

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
    void ScaleUpCanvasSize();
    void ScaleDownCanvasSize();
    SerialCode serial_status;
    DeviceArduinoDue* due;

private slots:
    void ToggleScanButton();
    void ToggleScaleResetButton();
    void ToggleScaleXPlusButton();
    void ToggleScaleYPlusButton();
    void ToggleScaleXMinusButton();
    void ToggleScaleYMinusButton();
    void TogglePlotInfoButton();
    void ToggleBinDirButton();

private:
    void SetupUi();
    void Update();
    int w;
    int h;
    int upper_widget_h;
    float scale_x_interval;
    float scale_y_interval;
    QVBoxLayout* layout;
    MetParaList* para_list;
    std::thread* thread;
    size_t count;
    QTimer* timer;
    Helper* helper;
    MetCanvas* canvas;
    MetButton* scan_button;
    MetButton* scale_reset_button;
    MetButton* scale_x_plus_button;
    MetButton* scale_y_plus_button;
    MetButton* scale_x_minus_button;
    MetButton* scale_y_minus_button;
    MetButton* plot_info_button;
    MetButton* bin_dir_button;
};

#endif