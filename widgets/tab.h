#ifndef TAB_H
#define TAB_H

#include <QTabWidget>
#include <QString>

#include "color.h"
#include "font.h"

class METTabStyle
{
public:
	METTabStyle(QString bkg_color = COLOR_LIGHT_GRAY,
				QString selection_bkg_color = COLOR_BLACK,
			    QString font_size = FONT_SIZE,
			    QString font_color = FONT_COLOR);
	~METTabStyle();

	QString bkg_color;
	QString selection_bkg_color;
	QString font_size;
	QString font_color;
};

class METTab : public QTabWidget
{
	Q_OBJECT // enable meta object abilities

public:
	METTab(METTabStyle style,
		   QWidget* parent = nullptr);
	~METTab();

private:
	METTabStyle style;
	QString style_sheet;
	void load_style_sheet();
};

#endif