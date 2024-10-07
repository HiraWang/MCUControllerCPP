#include "automation_view.h"

#include <QHBoxLayout>

AutomationView::AutomationView(int w,
                               int h,
                               MetParaList* para_list,
                               QWidget* parent) :
	w(w),
	h(h),
	para_list(para_list),
	QWidget(parent)
{
	SetupUi();
}

AutomationView::~AutomationView()
{

}

void AutomationView::SetupUi()
{
	setFixedWidth(w);
	setFixedHeight(h);
	LoadStyleSheet();

	MetProcessUnitStyle process_unit_style;
	process_unit_1 = new MetProcessUnit(process_unit_style,
									    "Stop pump channel 2",
										"Time 1:",
										this);
	process_unit_2 = new MetProcessUnit(process_unit_style,
										"Start pulse generator",
										"Time 2:",
										this);
	process_unit_3 = new MetProcessUnit(process_unit_style,
										"Start pump channel 2",
										"Time 3:",
										this);
	process_unit_4 = new MetProcessUnit(process_unit_style,
										"Stop pulse generator",
										"Time 4:",
										this);
	process_unit_5 = new MetProcessUnit(process_unit_style,
										"Stop pump channel 1 and 2",
										"Time 5:",
										this);
	all_process = new MetProcessUnit(process_unit_style,
								     "All process",
								     "Total time:",
								     this);
	all_process->time_edit->setText("");
	all_process->time_edit->setEnabled(false);
	all_process->label_name->setObjectName("all_process_name");
	all_process->label_name->setStyleSheet("QLabel#all_process_name {"
										   "background-color: " + QString(COLOR_BLACK) + ";"
										   "border-radius: 5px;"
										   "padding-left: 2px;"
										   "font: bold " + QString(FONT_SIZE) + ";"
										   "color: " + QString(COLOR_WHITE) + ";"
										   "}");
	all_process->time_edit->setStyleSheet("MetLineEdit {"
										  "background-color: transparent;"
										  "border: 0px;"
										  "font: bold " + QString(FONT_SIZE) + ";"
										  "color: " + QString(FONT_COLOR) + ";"
										  "}");

	MetButtonStyle button_style;
	button_set = new MetButton(button_style, "SET", "", 80, 80, "", "", this);
	button_run = new MetButton(button_style, "RUN", "STOP", 80, 80, "", "", this);

	QHBoxLayout* button_layout = new QHBoxLayout();
	button_layout->addStretch(10);
	button_layout->addWidget(button_set, 0, Qt::AlignCenter);
	button_layout->addStretch(1);
	button_layout->addWidget(button_run, 0, Qt::AlignCenter);
	button_layout->addStretch(10);

	layout = new QVBoxLayout(this);
	layout->addWidget(process_unit_1, 0, Qt::AlignCenter);
	layout->addWidget(process_unit_2, 0, Qt::AlignCenter);
	layout->addWidget(process_unit_3, 0, Qt::AlignCenter);
	layout->addWidget(process_unit_4, 0, Qt::AlignCenter);
	layout->addWidget(process_unit_5, 0, Qt::AlignCenter);
	layout->addWidget(all_process, 0, Qt::AlignCenter);
	layout->addItem(button_layout);
	setLayout(layout);
}

void AutomationView::LoadStyleSheet()
{
	style_sheet =
		"AutomationView {"
		"background-color: " + QString(COLOR_GRAY) + ";"
		"border: 2px solid black;"
		"border-radius: 10px;"
		"}";
	style_sheet_lcd =
		"QLCDNumber {"
		"background-color: " + QString(COLOR_BLACK) + ";"
		"border: 2px solid rgb(113, 113, 113);"
		"border-width: 3px;"
		"border-radius: 5px;"
		"color: " + QString(COLOR_WHITE) + ";"
		"font: " + QString(FONT_SIZE) + ";"
		"}";
	style_sheet_status_on =
		"background-color: " + QString(ON_COLOR_1) + ";"
		"border-radius: 2px;";
	style_sheet_status_off =
		"background-color: " + QString(OFF_COLOR_1) + ";"
		"border-radius: 2px;";
}