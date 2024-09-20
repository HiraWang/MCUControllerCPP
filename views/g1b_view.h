#ifndef G1B_VIEW_H
#define G1B_VIEW_H

#include <QWidget>
#include <QHBoxLayout>

#include "../utility.h"
#include "../widgets/buttons.h"
#include "../devices/device.h"

class G1BView : public QWidget
{
    Q_OBJECT // enable meta object abilities

public:
    G1BView(int w,
            int h, 
            METParaList* para_list,
            QWidget* parent = nullptr);
    ~G1BView();
    METButton* read_button;
    METButton* write_button;

private:
    int w;
    int h;
    DeviceG1B* G1B;
    QHBoxLayout* layout;
    METParaList* para_list;
    void setup_ui();
    void read();
    void write();
};

#endif