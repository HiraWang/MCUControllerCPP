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
}

void MetMenu::LoadStyleSheet()
{
	style_sheet =
		"QMenu {"
		"background-color: " + QString(COLOR_GRAY) + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: bold " + QString(FONT_SIZE) + ";"
		"color: " + QString(FONT_COLOR) + ";"
		"}"
		"QMenu::item {"
		"padding: 5px 10px 5px 10px;"
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