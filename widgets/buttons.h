#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QString>

#include "color.h"
#include "font.h"

class METButtonStyle
{
public:
	METButtonStyle(QString color_1 = COLOR_WHITE,
				   QString color_2 = COLOR_WHITE,
				   QString hover_color_1 = COLOR_LIGHT_GRAY,
				   QString hover_color_2 = COLOR_LIGHT_GRAY,
				   QString pressed_color_1 = COLOR_GRAY,
				   QString pressed_color_2 = COLOR_GRAY,
				   QString font_size = FONT_SIZE,
				   QString font_color = FONT_COLOR);
	~METButtonStyle();

	QString color_1;
	QString color_2;
	QString hover_color_1;
	QString hover_color_2;
	QString pressed_color_1;
	QString pressed_color_2;
	QString font_size;
	QString font_color;
};

class METButton : public QPushButton
{
	Q_OBJECT // enable meta object abilities

public:
	METButton(METButtonStyle style,
	     	  QString name_default,
			  QString name_pressed,
			  int w,
			  int h,
			  QString icon_path_default = "",
			  QString icon_path_pressed = "",
			  QWidget* parent = nullptr);
	~METButton();
	bool status;
	void set_button_default();
	void set_button_pressed();

private:
	METButtonStyle style;
	QString name_default;
	QString name_pressed;
	QString icon_path_default;
	QString icon_path_pressed;
	QString style_sheet_default;
	QString style_sheet_pressed;
	QIcon icon_default;
	QIcon icon_pressed;
	int w;
	int h;
	void load_style_sheet();
};

#endif