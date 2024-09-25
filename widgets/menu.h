#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "utility.h"
#include "widgets/line_edit.h"

class MetMenu : public QDialog
{
    Q_OBJECT // enable meta object abilities

public:
    MetMenu(MetParaList* para_list,
            QWidget* parent = nullptr);
    virtual ~MetMenu();
    void Show();
    void Close();
    void UpdateAttributes();
    QHBoxLayout** layout_list;
    MetLineEdit** line_edit_list;

private:
    void SetupUi();
    void AddAttribute(MetPara para,
                      QHBoxLayout* layout,
                      MetLineEdit* line_edit,
                      bool is_editable);
    QVBoxLayout* layout;
    MetParaList* para_list;
};

#endif