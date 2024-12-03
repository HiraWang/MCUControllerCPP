#ifndef MONITOR_VIEW_H
#define MONITOR_VIEW_H

#include <QElapsedTimer>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QTimer>
#include <QWidget>

#include "../utility.h"
#include "../devices/device.h"
#include "../widgets/button.h"
#include "../widgets/canvas.h"
#include "../widgets/label.h"
#include "../widgets/lcd.h"
#include "../widgets/menu.h"
#include "../widgets/slider.h"

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
    Helper* helper;

public slots:
    void ToggleScanButton();

protected:
    void mousePressEvent(QMouseEvent* event);

private slots:
    void ToggleScaleResetButton();
    void ToggleScaleXPlusButton();
    void ToggleScaleYPlusButton();
    void ToggleScaleXMinusButton();
    void ToggleScaleYMinusButton();
    void TogglePlotInfoButton();
    void ToggleRenderButton();
    void ToggleAnalyzeButton();
    void ToggleBufferDirButton();
    void ToggleResultDirButton();
    void ToggleDataOffsetSlider();

private:
    void SetupUi();
    void Update();
    bool call_analyze;
    int w;
    int h;
    float scale_x_interval;
    float scale_y_interval;
    QVBoxLayout* layout;
    MetParaList* para_list;
    std::thread* thread;
    QElapsedTimer* timer;
    QTimer* ui_timer;
    MetCanvas* canvas;
    MetButton* scan_button;
    MetButton* scale_reset_button;
    MetButton* scale_x_plus_button;
    MetButton* scale_y_plus_button;
    MetButton* scale_x_minus_button;
    MetButton* scale_y_minus_button;
    MetButton* plot_info_button;
    MetButton* render_button;
    MetButton* analyze_button;
    MetButton* buffer_dir_button;
    MetButton* result_dir_button;
    MetSlider* data_offset_slider;
    MetLcd* timer_lcd;
    MetLcd* signal_lcd;
    MetMenu* menu;
};

#endif