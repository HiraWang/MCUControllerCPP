#include "line_edit.h"

METLineEdit::METLineEdit(METLineEditStyle style,
						 int w,
						 int h,
						 QWidget* parent) :
	style(style),
	w(w),
	h(h),
	QLineEdit(parent)
{
	setFixedWidth(w);
	setFixedHeight(h);
	LoadStyleSheet();
	setStyleSheet(style_sheet);
}

METLineEdit::~METLineEdit()
{

}

void METLineEdit::LoadStyleSheet()
{
	style_sheet =
		"QLineEdit {"
		"background: " + style.bkg_color + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"font: " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}";
}

METLineEditStyle::METLineEditStyle(QString bkg_color,
								   QString font_size,
								   QString font_color) :
	bkg_color(bkg_color),
	font_size(font_size),
	font_color(font_color)
{

}

METLineEditStyle::~METLineEditStyle()
{

}