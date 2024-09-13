#include "buttons.h"

METButton::METButton(QString name_default,
				     QString name_pressed,
					 Style style,
					 int w,
				     int h,
					 QWidget* parent) :
	name_default(name_default),
	name_pressed(name_pressed),
	style(style),
	w(w),
	h(h),
	QPushButton(parent)
{
	this->setText(name_default);
	this->setFixedWidth(w);
	this->setFixedHeight(h);

	style_sheet = 
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
	this->setStyleSheet(style_sheet);
}

METButton::~METButton()
{

}