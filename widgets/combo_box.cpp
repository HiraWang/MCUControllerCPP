#include <iostream>

#include "combo_box.h"
#include "utility.h"

METComboBox::METComboBox(METComboBoxStyle style,
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
	load_style_sheet();
	setStyleSheet(style_sheet);
}

METComboBox::~METComboBox()
{

}

void METComboBox::load_style_sheet()
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
        "}"
        "QComboBox QAbstractItemView:item:hover {"
        "background: " + style.selection_bkg_color + ";"
        "}"
        "QComboBox QAbstractItemView:item:selected {"
        "background: " + style.selection_bkg_color + ";"
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
        "QComboBox::down-arrow {"
        "background-color: " + style.down_arrow_color + ";"
        "border: 2px solid black;"
        "border-bottom-left-radius: 4px;"
        "border-bottom-right-radius: 4px;"
        "width: 4px;"
        "height: 5px;"
        "}"
        "QComboBox::drop-down {"
        "background-color: " + style.drop_down_color + ";"
        "border-top-right-radius: 3px;"
        "border-bottom-right-radius: 3px;"
        "border-left: 2px solid black;"
        "}"
        "QComboBox:down-arrow:on {"
        "background-color: " + style.down_arrow_on_color + ";"
        "border: 2px solid black;"
        "border-bottom-left-radius: 4px;"
        "border-bottom-right-radius: 4px;"
        "width: 4px;"
        "height: 5px;"
        "}";
}

METComboBoxStyle::METComboBoxStyle(QString bkg_color,
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

METComboBoxStyle::~METComboBoxStyle()
{

}