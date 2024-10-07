#ifndef PROCESS_UNIT_H
#define PROCESS_UNIT_H

#include <QHBoxLayout>
#include <QLCDNumber>
#include <QWidget>
#include <QString>

#include "color.h"
#include "font.h"
#include "label.h"
#include "line_edit.h"

class MetProcessUnitStyle
{
public:
	MetProcessUnitStyle(QString bkg_color = COLOR_BLACK,
					    QString color_1 = ON_COLOR_1,
					    QString color_2 = OFF_COLOR_1,
						QString font_size = FONT_SIZE,
						QString font_color = COLOR_WHITE);
	virtual ~MetProcessUnitStyle();
	QString bkg_color;
	QString color_1;
	QString color_2;
	QString font_size;
	QString font_color;
};

class MetProcessUnit : public QWidget
{
	Q_OBJECT // enable meta object abilities

public:
	MetProcessUnit(MetProcessUnitStyle style,
				   QString name,	
				   QString time,	
				   QWidget* parent = nullptr);
	virtual ~MetProcessUnit();
	void StatusOn();
	void StatusOff();
	void SetLcd();
	MetLabel* label_name;
	MetLineEdit* time_edit;

private:
	void LoadStyleSheet();
	bool status;
	MetProcessUnitStyle style;
	QString style_sheet_lcd;
	QString style_sheet_status_on;
	QString style_sheet_status_off;
	QHBoxLayout* layout;
	MetLabel* label_time;
	MetLabel* label_unit;
	MetLabel* label_status;
	QLCDNumber* lcd;
};

#endif