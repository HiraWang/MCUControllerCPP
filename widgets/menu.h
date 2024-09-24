#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "utility.h"
#include "widgets/line_edit.h"

class METMenu : public QDialog
{
    Q_OBJECT // enable meta object abilities

public:
    METMenu(METParaList* para_list,
            QWidget* parent = nullptr);
    virtual ~METMenu();
    void show();
    void close();
    void update_attributes();
    QHBoxLayout** layout_list;
    METLineEdit** line_edit_list;

private:
    void setup_ui();
    void add_attribute(METPara para,
                       QHBoxLayout* layout,
                       METLineEdit* line_edit,
                       bool is_editable);
    QVBoxLayout* layout;
    METParaList* para_list;
};

#endif