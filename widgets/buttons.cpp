#include <iostream>

#include "buttons.h"
#include "utility.h"

METButton::METButton(METButtonStyle style,
					 QString name_default,
				     QString name_pressed,
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
	status = BUTTON_DEFAULT;
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
	status = BUTTON_PRESSED;
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

METButtonStyle::METButtonStyle(QString color_1,
							   QString color_2,
							   QString hover_color_1,
							   QString hover_color_2,
							   QString pressed_color_1,
							   QString pressed_color_2,
							   QString font_size,
							   QString font_color) :
	color_1(color_1),
	color_2(color_2),
	hover_color_1(hover_color_1),
	hover_color_2(hover_color_2),
	pressed_color_1(pressed_color_1),
	pressed_color_2(pressed_color_2),
	font_size(font_size),
	font_color(font_color)
{

}

METButtonStyle::~METButtonStyle()
{

}