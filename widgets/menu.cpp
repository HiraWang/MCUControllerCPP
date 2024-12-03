#include "menu.h"

#include "color.h"
#include "font.h"

MetMenu::MetMenu(QWidget* parent) :
	QMenu(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	LoadStyleSheet();
	SetupUi();
}

MetMenu::~MetMenu()
{

}

void MetMenu::SetupUi()
{
	setFixedWidth(200);
	setStyleSheet(style_sheet);
	MetMenuCustomStyle* style = new MetMenuCustomStyle();
	setStyle(style);
}

void MetMenu::LoadStyleSheet()
{
	style_sheet =
		"QMenu {"
		"background-color: " + QString(COLOR_GRAY) + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: 14px;"
		"color: " + QString(FONT_COLOR) + ";"
		"}"
		"QMenu::item {"
		"height: 20px;"
		"padding: 5px 0px 5px 10px;"
		"border-radius: 5px;"
		"}"
		"QMenu::item:hover {"
		"border-radius: 5px;"
		"background-color: " + QString(COLOR_WHITE) + ";"
		"}"
		"QMenu::item:selected {"
		"background-color: " + QString(COLOR_WHITE) + ";"
		"}";
}

int MetMenuCustomStyle::pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const
{
	if (metric == QStyle::PM_SmallIconSize) {
		return 24;
	}
	return QProxyStyle::pixelMetric(metric, option, widget);
}