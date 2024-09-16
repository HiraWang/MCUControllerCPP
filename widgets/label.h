#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QString>

#include "color.h"
#include "font.h"

class METLabelStyle
{
public:
	METLabelStyle(QString font_size = FONT_SIZE,
				  QString font_color = FONT_COLOR);
	~METLabelStyle();

	QString font_size;
	QString font_color;
};

class METLabel : public QLabel
{
	Q_OBJECT // enable meta object abilities

public:
	METLabel(METLabelStyle style,
			 QString name,
			 int w,
			 int h,
			 QWidget* parent = nullptr);
	~METLabel();

private:
	METLabelStyle style;
	QString name;
	QString style_sheet;
	int w;
	int h;
	void load_style_sheet();
};

#endif