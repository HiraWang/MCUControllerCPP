#ifndef G1B_VIEW_H
#define G1B_VIEW_H

#include <QHBoxLayout>
#include <QWidget>

#include "../utility.h"
#include "../devices/device.h"
#include "../widgets/button.h"

class G1BView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    G1BView(int w,
            int h, 
            MetParaList* para_list,
            QWidget* parent = nullptr);
    virtual ~G1BView();
    MetButton* read_button;
    MetButton* write_button;
    SerialCode serial_status;

private:
    void SetupUi();
    void Read();
    void Write();
    int w;
    int h;
    DeviceG1B* g1b;
    QHBoxLayout* layout;
    MetParaList* para_list;
};

#endif