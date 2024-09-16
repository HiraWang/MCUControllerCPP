#include "label.h"

METLabel::METLabel(METLabelStyle style,
				   QString name,
				   int w,
				   int h,
				   QWidget* parent) :
	style(style),
	w(w),
	h(h),
	QLabel(parent)
{
	setText(name);
	setFixedWidth(w);
	setFixedHeight(h);
	load_style_sheet();
	setStyleSheet(style_sheet);
}

METLabel::~METLabel()
{

}

void METLabel::load_style_sheet()
{
	style_sheet =
		"QLabel {"
		"min-width: 65px;"
		"min-height: 25px;"
		"font: bold " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}";
}

METLabelStyle::METLabelStyle(QString font_size, 
							 QString font_color) :
	font_size(font_size),
	font_color(font_color)
{
	
}

METLabelStyle::~METLabelStyle()
{

}