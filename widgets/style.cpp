#include "style.h"

Style::Style(QString color_1,
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

Style::~Style()
{

}