#ifndef MENU_H
#define MENU_H

#include <QMenu>
#include <QMouseEvent>
#include <QProxyStyle>
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

class MetMenuCustomStyle : public QProxyStyle
{
public:
    virtual int pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const;
};

#endif