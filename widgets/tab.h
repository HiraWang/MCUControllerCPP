#ifndef TAB_H
#define TAB_H

#include <QString>
#include <QTabWidget>

#include "color.h"
#include "font.h"

class METTabStyle
{
public:
	METTabStyle(QString bkg_color = COLOR_LIGHT_GRAY,
				QString selection_bkg_color = COLOR_BLACK,
			    QString font_size = FONT_SIZE,
			    QString font_color = FONT_COLOR);
	virtual ~METTabStyle();

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
	virtual ~METTab();

private:
	void LoadStyleSheet();
	METTabStyle style;
	QString style_sheet;
};

#endif