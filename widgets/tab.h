#ifndef TAB_H
#define TAB_H

#include <QString>
#include <QTabWidget>

#include "color.h"
#include "font.h"

class MetTabStyle
{
public:
	MetTabStyle(QString bkg_color = COLOR_GRAY,
			    QString hover_bkg_color = COLOR_DEEP_GRAY,
				QString selection_bkg_color = COLOR_BLACK,
			    QString font_size = FONT_SIZE,
			    QString font_color = COLOR_LIGHT_GRAY);
	virtual ~MetTabStyle();

	QString bkg_color;
	QString hover_bkg_color;
	QString selection_bkg_color;
	QString font_size;
	QString font_color;
};

class MetTab : public QTabWidget
{
	Q_OBJECT // enable meta object abilities

public:
	MetTab(MetTabStyle style,
		   QWidget* parent = nullptr);
	virtual ~MetTab();

private:
	void LoadStyleSheet();
	MetTabStyle style;
	QString style_sheet;
};

#endif