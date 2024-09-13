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
			  QWidget* parent = nullptr);
	~METButton();
	QString name_default;
	QString name_pressed;
	QString style_sheet;
	Style style;
	int w;
	int h;

private:
	bool status;
};

#endif