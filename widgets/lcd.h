#ifndef LCD_H
#define LCD_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLCDNumber>

#include "color.h"
#include "font.h"

class MetLcdStyle
{
public:
	MetLcdStyle(QString bkg_color,
			    QString border_color,
			    QString font_size = FONT_SIZE,
			    QString font_color = FONT_COLOR);
	virtual ~MetLcdStyle();
	QString bkg_color;
	QString border_color;
	QString font_size;
	QString font_color;
};

class MetLcd : public QLCDNumber
{
	Q_OBJECT // enable meta object abilities

public:
	MetLcd(MetLcdStyle style,
		   QString name,
		   QString unit,
		   int label_w,
		   int label_h,
		   int lcd_w,
		   int lcd_h,
		   QWidget* parent = nullptr);
	virtual ~MetLcd();

private:
	void SetupUi();
	void LoadStyleSheet();
	int label_w;
	int label_h;
	int lcd_w;
	int lcd_h;
	MetLcdStyle style;
	QString style_sheet_label;
	QString style_sheet_lcd;
	QString name;
	QString unit;
	QLabel* label_name;
	QLabel* label_unit;
	QHBoxLayout* layout;
};

#endif