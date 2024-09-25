#ifndef PUMP_CHANNEL_H
#define PUMP_CHANNEL_H

#include <QLabel>
#include <QString>

#include "color.h"
#include "font.h"

class METPumpChannelStyle
{
public:
	METPumpChannelStyle(QString font_size = FONT_SIZE,
					    QString font_color = FONT_COLOR);
	virtual ~METPumpChannelStyle();
	QString font_size;
	QString font_color;
};

class METPumpChannel : public QWidget
{
	Q_OBJECT // enable meta object abilities

public:
	METPumpChannel(METPumpChannelStyle style,
				   QString name,
				   int w,
				   int h,
				   QWidget* parent = nullptr);
	virtual ~METPumpChannel();

private:
	void LoadStyleSheet();
	int w;
	int h;
	METPumpChannelStyle style;
	QString style_sheet;
	QString name;
};

#endif