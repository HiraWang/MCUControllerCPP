#include <iostream>

#include "buttons.h"
#include "utility.h"

METButton::METButton(QString name_default,
				     QString name_pressed,
					 Style style,
					 int w,
				     int h,
					 QString icon_path_default,
					 QString icon_path_pressed,
					 QWidget* parent) :
	name_default(name_default),
	name_pressed(name_pressed),
	style(style),
	w(w),
	h(h),
	icon_path_default(icon_path_default),
	icon_path_pressed(icon_path_pressed),
	QPushButton(parent),
	status(false)
{
	if (icon_path_default.isEmpty() &&
		icon_path_pressed.isEmpty()) {
		setText(name_default);
	} else {
		icon_default = QIcon(icon_path_default);
		icon_pressed = QIcon(icon_path_pressed);
		setIcon(icon_default);
		setIconSize(QSize(w, h));
	}
	setFixedWidth(w);
	setFixedHeight(h);
	load_style_sheet();
	setStyleSheet(style_sheet_default);
}

METButton::~METButton()
{
	
}

void METButton::set_button_default()
{
	if (icon_path_default.isEmpty()) {
		setText(name_default);
	} else if (icon_path_default !=
			   icon_path_pressed) {
		setIcon(icon_default);
	}
	setStyleSheet(style_sheet_default);
	status = Status::DEFAULT;
}

void METButton::set_button_pressed()
{
	if (icon_path_pressed.isEmpty()) {
		setText(name_pressed);
	} else if (icon_path_default !=
		   	   icon_path_pressed) {
		setIcon(icon_pressed);
	}
	setStyleSheet(style_sheet_pressed);
	status = Status::PRESSED;
}

void METButton::load_style_sheet()
{
	style_sheet_default =
		"QPushButton {"
		"background-color: " + style.color_1 + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: bold " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}"
		"QPushButton:hover {"
		"background-color: " + style.hover_color_1 + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: bold " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}"
		"QPushButton:pressed {"
		"background-color: " + style.pressed_color_1 + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: bold " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}";
	style_sheet_pressed =
		"QPushButton {"
		"background-color: " + style.color_2 + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: bold " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}"
		"QPushButton:hover {"
		"background-color: " + style.hover_color_2 + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: bold " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}"
		"QPushButton:pressed {"
		"background-color: " + style.pressed_color_2 + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: bold " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}";
}