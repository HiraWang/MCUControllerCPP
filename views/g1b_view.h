#ifndef G1B_VIEW_H
#define G1B_VIEW_H

#include <QHBoxLayout>
#include <QWidget>

#include "../utility.h"
#include "../devices/device.h"
#include "../widgets/buttons.h"

class G1BView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    G1BView(int w,
            int h, 
            METParaList* para_list,
            QWidget* parent = nullptr);
    virtual ~G1BView();
    METButton* read_button;
    METButton* write_button;

private:
    void setup_ui();
    void read();
    void write();
    int w;
    int h;
    DeviceG1B* G1B;
    QHBoxLayout* layout;
    METParaList* para_list;
};

#endif