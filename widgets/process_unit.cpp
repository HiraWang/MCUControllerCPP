#include "process_unit.h"

MetProcessUnit::MetProcessUnit(MetProcessUnitStyle style,
							   QString name,
							   QString time,
							   QWidget* parent) :
	style(style),
	QWidget(parent)
{
	LoadStyleSheet();

	MetLabelStyle label_style_1(COLOR_BLACK, FONT_SIZE, COLOR_WHITE);
	label_name = new MetLabel(label_style_1, name, 225, 25, this);
	label_name->setObjectName("process_name");
	label_name->setStyleSheet("QLabel#process_name {"
							  "background-color: " + QString(COLOR_DEEP_GRAY) + ";"
							  "border-radius: 5px;"
							  "padding-left: 2px;"
							  "font: bold " + QString(FONT_SIZE) + ";"
							  "color: " + QString(COLOR_WHITE) + ";"
							  "}");

	MetLabelStyle label_style_2(FONT_SIZE, FONT_COLOR);
	label_time = new MetLabel(label_style_2, time, 120, 25, this);
	label_unit = new MetLabel(label_style_2, "s", 20, 25, this);
	label_status = new MetLabel(label_style_2, "", 25, 25, this);

	MetLineEditStyle line_edit_style;
	time_edit = new MetLineEdit(line_edit_style, 100, 25, this);

	lcd = new QLCDNumber();
	lcd->setFixedWidth(80);
	lcd->setFixedHeight(25);
	lcd->setStyleSheet(style_sheet_lcd);
	lcd->display(0);

	status = false;
	label_status->setStyleSheet(style_sheet_status_off);

	layout = new QHBoxLayout(this);
	layout->addWidget(label_name, 0, Qt::AlignLeft);
	layout->addWidget(label_time, 0, Qt::AlignCenter);
	layout->addWidget(time_edit, 0, Qt::AlignCenter);
	layout->addWidget(label_unit, 0, Qt::AlignCenter);
	layout->addWidget(lcd, 0, Qt::AlignCenter);
	layout->addWidget(label_status, 0, Qt::AlignRight);
	setLayout(layout);
}

MetProcessUnit::~MetProcessUnit()
{

}

void MetProcessUnit::LoadStyleSheet()
{
	style_sheet_lcd =
		"QLCDNumber {"
		"background-color: " + style.bkg_color + ";"
		"border: 2px solid rgb(113, 113, 113);"
		"border-width: 3px;"
		"border-radius: 5px;"
		"color: " + style.font_color + ";"
		"font: " + style.font_size + ";"
		"}";
	style_sheet_status_on =
		"background-color: " + style.color_1 + ";"
		"border-radius: 2px;";
	style_sheet_status_off =
		"background-color: " + style.color_2 + ";"
		"border-radius: 2px;";
}

void MetProcessUnit::StatusOn()
{

}

void MetProcessUnit::StatusOff()
{

}

void MetProcessUnit::SetLcd()
{

}

MetProcessUnitStyle::MetProcessUnitStyle(QString bkg_color,
										 QString color_1,
										 QString color_2,
								         QString font_size,
								         QString font_color) :
	bkg_color(bkg_color),
	color_1(color_1),
	color_2(color_2),
	font_size(font_size),
	font_color(font_color)
{

}

MetProcessUnitStyle::~MetProcessUnitStyle()
{

}