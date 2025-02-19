#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "utility.h"
#include "../widgets/button.h"
#include "../widgets/line_edit.h"
#include "../widgets/text_edit.h"

class MetDialog : public QDialog
{
    Q_OBJECT // enable meta object abilities

public:
    MetDialog(MetParaList* para_list,
              QWidget* parent = nullptr);
    virtual ~MetDialog();
    void Show();
    void Close();
    void UpdateAttributes();
    QHBoxLayout** layout_list;
    MetLineEdit** line_edit_list;

public slots:
    void ToggleRefreshButton();

private:
    void SetupUi();
    void AddAttribute(MetPara para,
                      QHBoxLayout* layout,
                      MetLineEdit* line_edit,
                      bool is_editable,
                      unsigned char* para_count);
    QVBoxLayout* layout;
    MetTextEdit* text;
    MetButton* refresh_button;
    MetParaList* para_list;
};

#endif