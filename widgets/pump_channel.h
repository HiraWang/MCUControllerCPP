#ifndef PUMP_CHANNEL_H
#define PUMP_CHANNEL_H

#include <QLabel>
#include <QString>

#include "color.h"
#include "font.h"

class MetPumpChannelStyle
{
public:
	MetPumpChannelStyle(QString font_size = FONT_SIZE,
					    QString font_color = FONT_COLOR);
	virtual ~MetPumpChannelStyle();
	QString font_size;
	QString font_color;
};

class MetPumpChannel : public QWidget
{
	Q_OBJECT // enable meta object abilities

public:
	MetPumpChannel(MetPumpChannelStyle style,
				   QString name,
				   int w,
				   int h,
				   QWidget* parent = nullptr);
	virtual ~MetPumpChannel();

private:
	void LoadStyleSheet();
	int w;
	int h;
	MetPumpChannelStyle style;
	QString style_sheet;
	QString name;
};

#endif