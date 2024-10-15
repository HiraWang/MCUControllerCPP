#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>
#include <QString>

#include "color.h"
#include "font.h"

class MetSliderStyle
{
public:
	MetSliderStyle(QString groove_color,
			       QString handle_color);
	virtual ~MetSliderStyle();
	QString groove_color;	
	QString handle_color;
};

class MetSlider : public QSlider
{
	Q_OBJECT // enable meta object abilities

public:
	MetSlider(MetSliderStyle style,
			  Qt::Orientation orient,
			  int w,
			  int h,
			  int min,
			  int max,
			  int interval,
			  QWidget* parent = nullptr);
	virtual ~MetSlider();

private:
	void LoadStyleSheet();
	int w;
	int h;
	MetSliderStyle style;
	QString style_sheet;
};

#endif