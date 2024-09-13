#ifndef STYLE_H
#define STYLE_H

#include <QObject>
#include <QString>
#include "color.h"
#include "font.h"

class Style
{
public:
	Style(QString color_1 = COLOR_WHITE,
		  QString color_2 = COLOR_WHITE,
		  QString hover_color_1 = COLOR_LIGHT_GRAY,
		  QString hover_color_2 = COLOR_LIGHT_GRAY,
		  QString pressed_color_1 = COLOR_GRAY,
		  QString pressed_color_2 = COLOR_GRAY,
		  QString font_size = FONT_SIZE,
		  QString font_color = FONT_COLOR);
	~Style();
	QString color_1;
	QString color_2;
	QString hover_color_1;
	QString hover_color_2;
	QString pressed_color_1;
	QString pressed_color_2;
	QString font_size;
	QString font_color;
};

#endif