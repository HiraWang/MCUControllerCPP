#ifndef G1B_VIEW_H
#define G1B_VIEW_H

#include <QVBoxLayout>
#include <QWidget>

#include "../utility.h"
#include "../devices/device.h"
#include "../widgets/button.h"
#include "../widgets/line_edit.h"

class G1BView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    G1BView(int w,
            int h, 
            MetParaList* para_list,
            QWidget* parent = nullptr);
    virtual ~G1BView();
    MetButton* freq_button;
    MetButton* pw_button;
    MetButton* voltage_button;
    MetButton* offset_button;
    MetButton* out_button;
    MetButton* read_button;
    MetButton* write_button;
    MetLineEdit* freq_edit;
    MetLineEdit* pw_edit;
    MetLineEdit* voltage_edit;
    MetLineEdit* offset_edit;
    DeviceG1B* g1b;
    SerialCode serial_status;

private slots:
    void SetupUi();
    void SetSerialStatusOk();
    void SetSerialStatusFail();
    void ToggleFreqButton();
    void TogglePwButton();
    void ToggleVoltageButton();
    void ToggleOffsetButton();
    void ToggleOutButton();

private:
    void Read();
    void Write();
    int w;
    int h;
    QVBoxLayout* layout;
    MetParaList* para_list;
};

#endif