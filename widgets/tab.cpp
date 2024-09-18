#include "tab.h"

METTab::METTab(METTabStyle style,
			   QWidget* parent) :
    style(style),
    QTabWidget(parent)
{
    QSizePolicy size_policy = sizePolicy();
    size_policy.setRetainSizeWhenHidden(true);
    setSizePolicy(size_policy);
    load_style_sheet();
    setStyleSheet(style_sheet);
}

METTab::~METTab()
{

}

void METTab::load_style_sheet()
{
    style_sheet =
        "QTabBar::tab {"
        "background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
        "                                  stop : 0 #A3A3A3, stop: 0 #DDDDDD,"
        "                                  stop: 0.6 #D8D8D8, stop: 1.0 #A3A3A3);"
        "border-top: 2px solid black;"
        "border-left: 2px solid black;"
        "border-right: 2px solid black;"
        "margin-right: -2px;"
        "min-width: 15ex;"
        "padding: 5px;"
        "font: bold " + style.font_size + ";"
        "color: " + style.bkg_color + ";"
        "}"
        "QTabBar::tab:selected {"
        "background-color: " + style.selection_bkg_color + ";"
        "border-top: 2px solid black;"
        "border-left: 2px solid black;"
        "border-right: 2px solid black;"
        "min-width: 15ex;"
        "padding: 5px;"
        "font: bold " + style.font_size + ";"
        "color: " + style.bkg_color + ";"
        "}"
        "QTabWidget:pane {"
        "background-color: " + style.bkg_color + ";"
        "border: 2px solid black;"
        "}";
}

METTabStyle::METTabStyle(QString bkg_color,
                         QString selection_bkg_color,
                         QString font_size,
                         QString font_color) :
    bkg_color(bkg_color),
    selection_bkg_color(selection_bkg_color),
    font_size(font_size),
    font_color(font_color)
{

}

METTabStyle::~METTabStyle()
{

}
