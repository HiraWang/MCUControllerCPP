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
	delete[] process_unit_list;
}

void AutomationView::SetupUi()
{
	setFixedWidth(w);
	setFixedHeight(h);
	LoadStyleSheet();

	MetProcessUnitStyle process_unit_style;
	unit_cnt = 5;
	process_unit_list = new MetProcessUnit* [unit_cnt + 1];
	process_unit_list[1] = new MetProcessUnit(process_unit_style, 1,
											  "Stop pump channel 2",
											  "Time 1:",
											  this);
	process_unit_list[2] = new MetProcessUnit(process_unit_style, 2,
											  "Start pulse generator",
											  "Time 2:",
											  this);
	process_unit_list[3] = new MetProcessUnit(process_unit_style, 3,
											  "Start pump channel 2",
											  "Time 3:",
											  this);
	process_unit_list[4] = new MetProcessUnit(process_unit_style, 4,
											  "Stop pulse generator",
											  "Time 4:",
											  this);
	process_unit_list[5] = new MetProcessUnit(process_unit_style, 5,
											  "Stop pump channel 1 and 2",
											  "Time 5:",
											  this);
	all_process = new MetProcessUnit(process_unit_style, 0,
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
	
	connect(button_set, &QPushButton::released, this,
		&AutomationView::ToggleSetButton);
	connect(button_run, &QPushButton::released, this,
		&AutomationView::ToggleRunButton);

	QHBoxLayout* button_layout = new QHBoxLayout();
	button_layout->addStretch(10);
	button_layout->addWidget(button_set, 0, Qt::AlignCenter);
	button_layout->addStretch(1);
	button_layout->addWidget(button_run, 0, Qt::AlignCenter);
	button_layout->addStretch(10);

	layout = new QVBoxLayout(this);
	layout->addWidget(process_unit_list[1], 0, Qt::AlignCenter);
	layout->addWidget(process_unit_list[2], 0, Qt::AlignCenter);
	layout->addWidget(process_unit_list[3], 0, Qt::AlignCenter);
	layout->addWidget(process_unit_list[4], 0, Qt::AlignCenter);
	layout->addWidget(process_unit_list[5], 0, Qt::AlignCenter);
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

void AutomationView::ToggleSetButton()
{
	button_set->SetButtonDefault();
	process_unit_list[1]->time = (int)(process_unit_list[1]->time_edit->text().toInt());
	process_unit_list[2]->time = (int)(process_unit_list[2]->time_edit->text().toInt());
	process_unit_list[3]->time = (int)(process_unit_list[3]->time_edit->text().toInt());
	process_unit_list[4]->time = (int)(process_unit_list[4]->time_edit->text().toInt());
	process_unit_list[5]->time = (int)(process_unit_list[5]->time_edit->text().toInt());
	for (int i = 1; i <= unit_cnt; i++) {
		process_unit_list[i]->time_tot = 0;
		for (int j = 1; j <= process_unit_list[i]->id; j++) {
			process_unit_list[i]->time_tot += process_unit_list[j]->time;
		}
		std::cout << "process unit " << i << " time_tot " << process_unit_list[i]->time_tot << '\n';
		process_unit_list[i]->StatusOff();
		process_unit_list[i]->SetLcd(process_unit_list[i]->time_edit->text());
	}
	time_tot = process_unit_list[unit_cnt]->time_tot;
	all_process->time_edit->setText(QString::number(time_tot));
	all_process->SetLcd("0");
}

void AutomationView::ToggleRunButton()
{
	if (button_run->status) {
		button_run->SetButtonDefault();
	} else {
		button_run->SetButtonPressed();
	}
}