#include "lcd.h"

MetLcd::MetLcd(MetLcdStyle style,
			   QString name,
			   QString unit,
			   int label_w,
			   int label_h,
			   int lcd_w,
			   int lcd_h,
			   QWidget* parent) :
	style(style),
	name(name),
	unit(unit),
	label_w(label_w),
	label_h(label_h), 
	lcd_w(lcd_w),
	lcd_h(lcd_h),
	QLCDNumber(parent)
{
	LoadStyleSheet();
	SetupUi();
}

MetLcd::~MetLcd()
{

}

void MetLcd::SetupUi()
{
	label_name = new QLabel(this);
	label_name->setText(name);
	label_name->setFixedSize(QSize(label_w, label_h));
	label_name->setStyleSheet(style_sheet_label);
	label_name->setContentsMargins(10, 0, 0, 5);

	setFixedSize(QSize(label_w + lcd_w, lcd_h));
	setStyleSheet(style_sheet_lcd);
	display(0);

	label_unit = new QLabel(this);
	label_unit->setText(unit);
	label_unit->setFixedSize(QSize(40, label_h));
	label_unit->setStyleSheet(style_sheet_label);

	layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(label_name, 0, { Qt::AlignLeft, Qt::AlignVCenter });
	layout->addWidget(this, 0, { Qt::AlignRight, Qt::AlignVCenter });
	layout->addWidget(label_unit, 0, { Qt::AlignRight, Qt::AlignVCenter });
	setLayout(layout);
}

void MetLcd::LoadStyleSheet()
{
	style_sheet_label =
		"QLabel {"
		"background-color: " + QString("transparent") + ";"
		"font: 12px;"
		"color: " + COLOR_WHITE + ";"
		"}";
	style_sheet_lcd =
		"QLCDNumber {"
		"background-color: " + style.bkg_color + ";"
		"border: 2px solid " + style.border_color + ";"
		"border-width: 3px;"
		"border-radius: 5px;"
		"color: " + style.font_size + ";"
		"font: " + style.font_color + ";"
		"}";
}

MetLcdStyle::MetLcdStyle(QString bkg_color,
						 QString border_color,
					     QString font_size,
					     QString font_color) :
	bkg_color(bkg_color),
	border_color(border_color),
	font_size(font_size),
	font_color(font_color)
{

}

MetLcdStyle::~MetLcdStyle()
{

}