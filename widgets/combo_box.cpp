#include "combo_box.h"

MetComboBox::MetComboBox(MetComboBoxStyle style,
					     int w,
					     int h,
					     QWidget* parent) :
	style(style),
	w(w),
	h(h),
	QComboBox(parent)
{
	setFixedWidth(w);
	setFixedHeight(h);
	LoadStyleSheet();
	setStyleSheet(style_sheet);
}

MetComboBox::~MetComboBox()
{

}

void MetComboBox::LoadStyleSheet()
{
    style_sheet =
        "QComboBox {"
        "min-height: 25px;"
        "border: 2px solid black;"
        "border-radius: 5px;"
        "padding-left: 7px;"
        "font: bold " + style.font_size + ";"
        "color: " + style.font_color + ";"
        "}"
        "QComboBox QAbstractItemView {"
        "min-height: 25px;"
        "border: 2px solid black;"
        "font: bold " + style.font_size + ";"
        "color: " + style.font_color + ";"
        "}"
        "QComboBox QAbstractItemView:item {"
        "background: " + style.bkg_color + ";"
        "min-width: 15ex;"
        "padding: 5px;"
        // remove the dotted line of focus rect
        "border-left: -6px solid black;"
        "}"
        "QComboBox QAbstractItemView:item:hover {"
        "background: " + style.selection_bkg_color + ";"
        "}"
        "QComboBox QAbstractItemView:item:selected {"
        "background: " + style.selection_bkg_color + ";"
        "color: " + style.hover_color + ";"
        "}"
        // remove the dotted line of focus rect
        "QComboBox QAbstractItemView:item:selected:focus {"
        "border: -6px solid black;"
        "}"
        "QComboBox:!editable, QComboBox::drop-down:editable {"
        "background: " + style.editable_color + ";"
        "}"
        "QComboBox:disabled {"
        "background: " + style.disabled_color + ";"
        "}"
        "QComboBox:hover {"
        "background-color: " + style.hover_color + ";"
        "}"
        "QComboBox::drop-down {"
        "background-color: " + style.down_arrow_color + ";"
        "border-top-right-radius: 3px;"
        "border-bottom-right-radius: 3px;"
        "margin: -1px;"
        "}"
        "QComboBox::down-arrow {"
        "image: url(:/images/ArrowDown.png);"
        "width: 20px;"
        "height: 20px;"
        "}"
        "QComboBox:down-arrow:on {"
        "image: url(:/images/ArrowUp.png);"
        "width: 20px;"
        "height: 20px;"
        "}";
}

MetComboBoxStyle::MetComboBoxStyle(QString bkg_color,
                                   QString selection_bkg_color,
                                   QString editable_color,
                                   QString disabled_color,
                                   QString hover_color,
                                   QString drop_down_color,
                                   QString down_arrow_color,
                                   QString down_arrow_on_color,
                                   QString font_size,
                                   QString font_color) :
    bkg_color(bkg_color),
    selection_bkg_color(selection_bkg_color),
    editable_color(editable_color),
    disabled_color(disabled_color),
    hover_color(hover_color),
    drop_down_color(drop_down_color),
    down_arrow_color(down_arrow_color),
    down_arrow_on_color(down_arrow_on_color),
    font_size(font_size),
    font_color(font_color)
{

}

MetComboBoxStyle::~MetComboBoxStyle()
{

}