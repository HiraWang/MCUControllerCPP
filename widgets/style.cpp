#include "style.h"

Style::Style(QString met_button_color_1,
			 QString met_button_color_2,
			 QString met_button_hover_color_1,
			 QString met_button_hover_color_2,
			 QString met_button_pressed_color_1,
			 QString met_button_pressed_color_2,
			 QString font_size,
			 QString font_color) :
	met_button_color_1(met_button_color_1),
	met_button_color_2(met_button_color_2),
	met_button_hover_color_1(met_button_hover_color_1),
	met_button_hover_color_2(met_button_hover_color_2),
	met_button_pressed_color_1(met_button_pressed_color_1),
	met_button_pressed_color_2(met_button_pressed_color_2),
	font_size(font_size),
	font_color(font_color)
{

}

Style::~Style()
{

}