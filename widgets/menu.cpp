#include "menu.h"

#include "color.h"
#include "font.h"

MetMenu::MetMenu(QWidget* parent) :
	QMenu(parent)
{

}

MetMenu::~MetMenu()
{

}

void MetMenu::SetupUi()
{
	setStyleSheet(style_sheet);
}

void MetMenu::LoadStyleSheet()
{
	style_sheet =
		"QDialog {"
		"background-color: " + QString(COLOR_GRAY) + ";"
		"border: 2px solid black;"
		"font: bold " + QString(FONT_SIZE) + ";"
		"color: " + QString(FONT_COLOR) + ";"
		"}";
}