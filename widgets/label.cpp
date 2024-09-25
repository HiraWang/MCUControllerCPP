#include "label.h"

MetLabel::MetLabel(MetLabelStyle style,
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
	LoadStyleSheet();
	setStyleSheet(style_sheet);
}

MetLabel::~MetLabel()
{

}

void MetLabel::LoadStyleSheet()
{
	style_sheet =
		"QLabel {"
		"min-width: 65px;"
		"min-height: 25px;"
		"font: bold " + style.font_size + ";"
		"color: " + style.font_color + ";"
		"}";
}

MetLabelStyle::MetLabelStyle(QString font_size, 
							 QString font_color) :
	font_size(font_size),
	font_color(font_color)
{
	
}

MetLabelStyle::~MetLabelStyle()
{

}