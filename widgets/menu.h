#ifndef MENU_H
#define MENU_H

#include <QMenu>
#include <QVBoxLayout>

#include "utility.h"

class MetMenu : public QMenu
{
    Q_OBJECT // enable meta object abilities

public:
    MetMenu(QWidget* parent = nullptr);
    virtual ~MetMenu();

private:
    void SetupUi();
    void LoadStyleSheet();
    QString style_sheet;
    QVBoxLayout* layout;
};

#endif