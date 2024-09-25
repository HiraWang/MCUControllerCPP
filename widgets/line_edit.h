#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <QLineEdit>
#include <QString>

#include "color.h"
#include "font.h"

class MetLineEditStyle
{
public:
	MetLineEditStyle(QString bkg_color = COLOR_WHITE, 
					 QString font_size = FONT_SIZE,
					 QString font_color = FONT_COLOR);
	virtual ~MetLineEditStyle();
	QString bkg_color;
	QString font_size;
	QString font_color;
};

class MetLineEdit : public QLineEdit
{
	Q_OBJECT // enable meta object abilities

public:
	MetLineEdit(MetLineEditStyle style,
			    int w,
			    int h,
			    QWidget* parent = nullptr);
	virtual ~MetLineEdit();

private:
	void LoadStyleSheet();
	int w;
	int h;
	MetLineEditStyle style;
	QString style_sheet;
};

#endif