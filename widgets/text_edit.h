#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <QPlainTextEdit>
#include <QString>

#include "color.h"
#include "font.h"

class MetTextEditStyle
{
public:
	MetTextEditStyle(QString bkg_color = COLOR_LIGHT_GRAY,
					 QString font_size = FONT_SIZE,
					 QString font_color = FONT_COLOR);
	virtual ~MetTextEditStyle();
	QString bkg_color;
	QString font_size;
	QString font_color;
};

class MetTextEdit : public QPlainTextEdit
{
	Q_OBJECT // enable meta object abilities

public:
	MetTextEdit(MetTextEditStyle style,
				int w,
				int h,
				QWidget* parent = nullptr);
	virtual ~MetTextEdit();

private:
	void LoadStyleSheet();
	int w;
	int h;
	MetTextEditStyle style;
	QString style_sheet;
};

#endif