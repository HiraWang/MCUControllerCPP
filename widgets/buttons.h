#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QString>

#include "color.h"
#include "font.h"

class MetButtonStyle
{
public:
	MetButtonStyle(QString color_1 = COLOR_WHITE,
				   QString color_2 = COLOR_WHITE,
				   QString hover_color_1 = COLOR_LIGHT_GRAY,
				   QString hover_color_2 = COLOR_LIGHT_GRAY,
				   QString pressed_color_1 = COLOR_GRAY,
				   QString pressed_color_2 = COLOR_GRAY,
				   QString font_size = FONT_SIZE,
				   QString font_color = FONT_COLOR);
	virtual ~MetButtonStyle();
	QString color_1;
	QString color_2;
	QString hover_color_1;
	QString hover_color_2;
	QString pressed_color_1;
	QString pressed_color_2;
	QString font_size;
	QString font_color;
};

class MetButton : public QPushButton
{
	Q_OBJECT // enable meta object abilities

public:
	MetButton(MetButtonStyle style,
	     	  QString name_default,
			  QString name_pressed,
			  int w,
			  int h,
			  QString icon_path_default = "",
			  QString icon_path_pressed = "",
			  QWidget* parent = nullptr);
	virtual ~MetButton();
	void SetButtonDefault();
	void SetButtonPressed();
	bool status;

private:
	void LoadStyleSheet();
	int w;
	int h;
	MetButtonStyle style;
	QString name_default;
	QString name_pressed;
	QString icon_path_default;
	QString icon_path_pressed;
	QString style_sheet_default;
	QString style_sheet_pressed;
	QIcon icon_default;
	QIcon icon_pressed;
};

#endif