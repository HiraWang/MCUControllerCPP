#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <QLineEdit>
#include <QString>

#include "color.h"
#include "font.h"

class METLineEditStyle
{
public:
	METLineEditStyle(QString bkg_color = COLOR_WHITE, 
					 QString font_size = FONT_SIZE,
					 QString font_color = FONT_COLOR);
	~METLineEditStyle();

	QString bkg_color;
	QString font_size;
	QString font_color;
};

class METLineEdit : public QLineEdit
{
	Q_OBJECT // enable meta object abilities

public:
	METLineEdit(METLineEditStyle style,
			    int w,
			    int h,
			    QWidget* parent = nullptr);
	~METLineEdit();

private:
	METLineEditStyle style;
	QString style_sheet;
	int w;
	int h;
	void load_style_sheet();
};

#endif