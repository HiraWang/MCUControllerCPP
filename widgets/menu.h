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
    ~METMenu();
    METLineEdit** line_edit_list;
    QHBoxLayout** layout_list;
    void show();
    void close();
    void update_attributes();

private:
    METParaList* para_list;
    QVBoxLayout* layout;
    void setup_ui();
    void add_attribute(METPara para,
                       QHBoxLayout* layout,
                       METLineEdit* line_edit,
                       bool is_editable);
};

#endif