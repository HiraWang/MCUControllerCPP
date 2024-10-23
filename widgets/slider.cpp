#include "slider.h"

MetSlider::MetSlider(MetSliderStyle style,
				     Qt::Orientation orient,
				     int w,
				     int h,
				     int min, 
					 int max,
					 int interval,
				     QWidget* parent) :
	style(style),
	w(w),
	h(h),
	QSlider(orient, parent)
{
	LoadStyleSheet();
	setStyleSheet(style_sheet);
	setMinimum(min);
	setMaximum(max);
	setTickPosition(QSlider::TicksAbove);
	setTickInterval(interval);
}

MetSlider::~MetSlider()
{

}

void MetSlider::LoadStyleSheet()
{
	style_sheet =
		"QSlider::groove:horizaontal {"
		"width: " + QString::number(w) + ";"
		"height: " + QString::number(h) + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"background-color: " + style.groove_color + ";"
		"}"
		"QSlider::groove:vertical {"
		"width: " + QString::number(w) + ";"
		"height: " + QString::number(h) + ";"
		"border: 2px solid black;"
		"border-radius: 5px;"
		"background-color: " + style.groove_color + ";"
		"}"
		"QSlider::handle:horizaontal {"
		"width: " + QString::number(h) + ";"
		"height: " + QString::number(h) + ";"
		"border: 2px solid black;"
		"background-color: " + style.handle_color + ";"
		"}"
		"QSlider::handle:vertical {"
		"width: " + QString::number(w + 100) + ";"
		"height: " + QString::number(w) + ";"
		"border: 2px solid black;"
		"background-color: " + style.handle_color + ";"
		"}";
}

MetSliderStyle::MetSliderStyle(QString groove_color,
							   QString handle_color) :
	groove_color(groove_color),
	handle_color(handle_color)
{

}

MetSliderStyle::~MetSliderStyle()
{

}