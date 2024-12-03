#include "tab.h"

MetTab::MetTab(MetTabStyle style,
			   QWidget* parent) :
    style(style),
    QTabWidget(parent)
{
    QSizePolicy size_policy = sizePolicy();
    size_policy.setRetainSizeWhenHidden(true);
    setSizePolicy(size_policy);
    LoadStyleSheet();
    setStyleSheet(style_sheet);
}

MetTab::~MetTab()
{

}

void MetTab::LoadStyleSheet()
{
    style_sheet =
        "QTabBar::tab {"
        "background-color: " + style.bkg_color + ";"
        "border-top: 2px solid black;"
        "border-left: 2px solid black;"
        "border-right: 2px solid black;"
        "border-bottom: 2px solid black;"
        "margin-right: -2px;"
        "margin-bottom: -2px;"
        "min-width: 15ex;"
        "padding: 5px;"
        "font: bold " + style.font_size + ";"
        "color: " + style.hover_bkg_color + ";"
        "}"
        "QTabBar::tab:hover {"
        "background-color: " + style.hover_bkg_color + ";"
        "border-top: 2px solid black;"
        "border-left: 2px solid black;"
        "border-right: 2px solid black;"
        "min-width: 15ex;"
        "padding: 5px;"
        "font: bold " + style.font_size + ";"
        "color: " + style.font_color + ";"
        "}"
        "QTabBar::tab:selected {"
        "background-color: " + style.selection_bkg_color + ";"
        "border-top: 2px solid black;"
        "border-left: 2px solid black;"
        "border-right: 2px solid black;"
        "border-top-left-radius: 6px;"
        "border-top-right-radius: 6px;"
        "min-width: 15ex;"
        "padding: 5px;"
        "font: bold " + style.font_size + ";"
        "color: " + style.font_color + ";"
        "}"
        "QTabBar::tab:!selected {"
        "margin-top: 6px;"
        "}"
        "QTabBar::tab:last:!selected {"
        "margin-right: -1px;"
        "border-right: 3px solid black;"
        "}"
        "QTabBar::tab:last:selected {"
        "margin-right: 0px;"
        "}"
        "QTabBar::tab:only-one {"
        "margin-right: 0px;"
        "border-top-left-radius: 6px;"
        "border-top-right-radius: 6px;"
        "margin-top: 6px;"
        "}"
        "QTabWidget:pane {"
        "background-color: " + QString(COLOR_LIGHT_GRAY) + ";"
        "border: 2px solid black;"
        "}";
}

MetTabStyle::MetTabStyle(QString bkg_color,
                         QString hover_bkg_color,
                         QString selection_bkg_color,
                         QString font_size,
                         QString font_color) :
    bkg_color(bkg_color),
    hover_bkg_color(hover_bkg_color),
    selection_bkg_color(selection_bkg_color),
    font_size(font_size),
    font_color(font_color)
{

}

MetTabStyle::~MetTabStyle()
{

}
