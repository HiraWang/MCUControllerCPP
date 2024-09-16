#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QString>

#include "style.h"

class METButton : public QPushButton
{
	Q_OBJECT // enable meta object abilities

public:
	METButton(QString name_default,
			  QString name_pressed,
			  Style style,
			  int w,
			  int h,
			  QString icon_path_default = "",
			  QString icon_path_pressed = "",
			  QWidget* parent = nullptr);
	~METButton();
	QString name_default;
	QString name_pressed;
	QString style_sheet_default;
	QString style_sheet_pressed;
	QString icon_path_default;
	QString icon_path_pressed;
	Style style;
	int w;
	int h;
	bool status;
	QIcon icon_default;
	QIcon icon_pressed;
	void set_button_default();
	void set_button_pressed();

private:
	void load_style_sheet();
};

#endif