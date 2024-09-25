#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QString>

#include "color.h"
#include "font.h"

class MetLabelStyle
{
public:
	MetLabelStyle(QString bkg_color, 
				  QString font_size = FONT_SIZE,
				  QString font_color = FONT_COLOR);
	virtual ~MetLabelStyle();
	QString bkg_color;
	QString font_size;
	QString font_color;
};

class MetLabel : public QLabel
{
	Q_OBJECT // enable meta object abilities

public:
	MetLabel(MetLabelStyle style,
			 QString name,
			 int w,
			 int h,
			 QWidget* parent = nullptr);
	virtual ~MetLabel();

private:
	void LoadStyleSheet();
	int w;
	int h;
	MetLabelStyle style;
	QString style_sheet;
	QString name;
};

#endif