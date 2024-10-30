#include "automation_view.h"

#include <QHBoxLayout>

#include "../widgets/msg_subwindow.h"

extern bool g_normal;
extern bool g_ui_test;

AutomationView::AutomationView(int w,
                               int h,
							   DeviceG1B* g1b,
							   DeviceRegloIcc* reglo_icc,
                               QWidget* parent) :
	w(w),
	h(h),
	serial_status(SERIAL_FAIL),
	g1b(g1b),
	reglo_icc(reglo_icc),
	QWidget(parent)
{
	InitLists();

	if (g_ui_test) {
		serial_status = SERIAL_OK;
		SetupUi();
		return;
	}

	if (!g1b || !reglo_icc) {
		serial_status = SERIAL_FAIL;
		MetMsgSubwindow("device G1B and RegloIcc not found");
		return;
	} else {
		serial_status = SERIAL_OK;
		g_out << "found device G1B and RegloIcc" << '\n';
		SetupUi();
	}
}

AutomationView::~AutomationView()
{
	if (g1b && reglo_icc) {
		delete[] process_unit_list;
	}
}

void AutomationView::InitLists()
{
	process_name_list = {
		"Start pump channel 1 and 2",
		"Stop pump channel 2",
		"Start pulse generator",
		"Start pump channel 2",
		"Stop pulse generator",
		"Stop pump channel 1 and 2"
	};

	process_function_list = {
		&AutomationView::StartPumpAllChannel,
		&AutomationView::StopPumpChannelNo2,
		&AutomationView::StartPulseGenerator,
		&AutomationView::StartPumpChannelNo2,
		&AutomationView::StopPulseGenerator,
		&AutomationView::StopPumpAllChannel
	};

	parameter_name_list = {
		"rpm",
		"dir",
		"freq",
		"pw",
		"voltage",
		"offset"
	};

	parameter_function_list = {
		&AutomationView::GetRpm,
		&AutomationView::GetDir,
		&AutomationView::GetFreq,
		&AutomationView::GetPw,
		&AutomationView::GetVoltage,
		&AutomationView::GetOffset
	};
}

void AutomationView::SetupUi()
{
	setFixedWidth(w);
	setFixedHeight(h);
	LoadStyleSheet();

	// prepare process units
	MetProcessUnitStyle process_unit_style;
	unit_cnt = 6;
	process_unit_list = new MetProcessUnit* [unit_cnt];
	for (int i = 0; i < unit_cnt; i++) {
		QString name = QString::fromStdString(process_name_list.front());
		process_name_list.pop_front();
		QString time = QString("Time ") + QString::number(i) + QString(":");
		bool is_normal_unit = (i == 0) ? false : true;
		process_unit_list[i] = new MetProcessUnit(process_unit_style,
												  i,
												  name,
												  time,
											      is_normal_unit,
												  this);
	}
	process_unit_list[0]->time = 0;
	process_unit_list[0]->time_tot = 0;
	process_unit_list[0]->time_edit->setText("0");
	process_unit_list[0]->time_edit->setEnabled(false);
	
	// prepare all process unit
	all_process = new MetProcessUnit(process_unit_style, 0,
								     "All process",
								     "Total time:",
								     false,
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
	button_run = new MetButton(button_style, "RUN", "STOP", 80, 80, "", "", this);
	
	connect(button_run, &QPushButton::released, this,
		&AutomationView::ToggleRunButton);
	
	bar = new QProgressBar(this);
	bar->setFixedWidth(process_unit_list[0]->width() - 15);
	bar->setRange(0, 100);
	bar->reset();
	bar->setStyleSheet("QProgressBar::chunk {"
					   "border-radius: 3px;"
					   "background: " + QString(COLOR_ON_1) + ";"
					   "}"
					   "QProgressBar {"
					   "background: " + QString(COLOR_DEEP_GRAY) + ";"
					   "border: 2px solid black;"
					   "text-align:center;"
					   "color: #fff;"
					   "height: 25px;"
					   "border-radius: 5px;"
					   "}");

	QWidget* container_automation = new QWidget(this);
	QWidget* container_pulse_gen = new QWidget(this);
	QWidget* container_pump = new QWidget(this);
	container_pulse_gen->setObjectName("pulse_gen_container");
	container_pulse_gen->setFixedWidth((width() - 750) / 2);
	container_pulse_gen->setFixedHeight(height()- 9);
	container_pulse_gen->setStyleSheet("QWidget#pulse_gen_container {"
									   "background-color: " + QString(COLOR_GRAY) + ";"
									   "border-radius: 10px;"
									   "}");
	container_automation->setFixedWidth(700);
	container_automation->setFixedHeight(height());
	container_pump->setObjectName("pump_container");
	container_pump->setFixedWidth((width() - 750) / 2);
	container_pump->setFixedHeight(height() - 9);
	container_pump->setStyleSheet("QWidget#pump_container {"
								  "background-color: " + QString(COLOR_GRAY) + ";"
								  "border-radius: 10px;"
								  "}");

	QVBoxLayout* layout_automation = new QVBoxLayout();
	QVBoxLayout* layout_pulse_gen = new QVBoxLayout();
	QVBoxLayout* layout_pump = new QVBoxLayout();
	layout_automation->setContentsMargins(0, 0, 0, 0);
	layout_pulse_gen->setContentsMargins(0, 0, 0, 0);
	layout_pump->setContentsMargins(0, 0, 0, 0);

	MetTreeStyle tree_style;
	tree = new MetTree(tree_style, (width() - 750) / 2, height() - 9, this);
	layout_pulse_gen->addWidget(tree, 0, Qt::AlignCenter);
	container_pulse_gen->setLayout(layout_pulse_gen);

	layout_automation->addStretch(1);
	for (int i = 0; i < unit_cnt; i++) {
		layout_automation->addWidget(process_unit_list[i], 0, Qt::AlignCenter);
	}
	layout_automation->addWidget(all_process, 0, Qt::AlignCenter);
	layout_automation->addStretch(1);
	layout_automation->addWidget(bar, 0, Qt::AlignCenter);
	layout_automation->addStretch(1);
	layout_automation->addWidget(button_run, 0, Qt::AlignCenter);
	layout_automation->addStretch(1);
	container_automation->setLayout(layout_automation);

	layout = new QHBoxLayout(this);
	layout->addWidget(container_pulse_gen, 0, { Qt::AlignLeft, Qt::AlignVCenter });
	layout->addWidget(container_automation, 0, Qt::AlignCenter);
	layout->addWidget(container_pump, 0, { Qt::AlignRight, Qt::AlignVCenter });
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
		"background-color: " + QString(COLOR_ON_1) + ";"
		"border-radius: 2px;";
	style_sheet_status_off =
		"background-color: " + QString(COLOR_OFF_1) + ";"
		"border-radius: 2px;";
}

void AutomationView::Set()
{
	InitLists();
	for (int i = 0; i < unit_cnt; i++) {
		MetProcessUnit* unit_anchor = process_unit_list[i];
		unit_anchor->time = (int)(unit_anchor->time_edit->text().toInt());
		unit_anchor->time_tot = 0;
		for (int j = 0; j <= unit_anchor->id; j++) {
			MetProcessUnit* unit_cursor = process_unit_list[j];
			unit_anchor->time_tot += unit_cursor->time;
		}
		unit_anchor->StatusOff();
		unit_anchor->SetLcd(unit_anchor->time_edit->text());
	}
	time_tot = process_unit_list[unit_cnt - 1]->time_tot;
	all_process->time_edit->setText(QString::number(time_tot));
	all_process->StatusOff();
	all_process->SetLcd("0");
	bar->reset();

	while (parameter_name_list.size() > 0) {
		QString name = QString::fromStdString(parameter_name_list.front());
		parameter_name_list.pop_front();

		QList<QTreeWidgetItem*> list = tree->findItems(name, Qt::MatchContains | Qt::MatchRecursive, 0);
		MetTreeData data = (this->*parameter_function_list.front())();

		int i = 0;
		foreach(QTreeWidgetItem * item, list) {
			item->setText(1, QString::number(data.value[i++]));
		}

		parameter_function_list.pop_front();
	}
}

void AutomationView::ToggleRunButton()
{
	if (button_run->status) {
		button_run->SetButtonDefault();
		StopProcess();
	} else {
		Set();
		button_run->SetButtonPressed();
		RunProcess();
	}
}

void AutomationView::RunProcess()
{
	thread = new QThread(this);
	worker = new TimerWorker(this);
	worker->moveToThread(thread);

	connect(worker, &TimerWorker::TimeOut, this, &AutomationView::Update);
	connect(thread, &QThread::started, worker, &TimerWorker::Start);
	connect(thread, &QThread::finished, worker, &TimerWorker::Finish);

	(this->*process_function_list.front())();
	process_function_list.pop_front();
	process_unit_list[0]->StatusOn();
	
	worker->Reset();
	thread->start();
}

void AutomationView::StopProcess()
{
	thread->terminate();
	StopPulseGenerator();
	StopPumpAllChannel();
}

void AutomationView::Update(int count)
{
	bar->setValue(roundf((float)(count) / (float)(time_tot) * 100.0f));
	all_process->SetLcd(QString::number(count));
	MetProcessUnit** list = process_unit_list;
	g_out << count << '\n';

	for (int i = 1; i < unit_cnt; i++) {
		if (list[i - 1]->time_tot < count && count <= list[i]->time_tot) {
			list[i]->time -= 1;
			list[i]->SetLcd(QString::number(list[i]->time));
			if (count == list[i]->time_tot) {
				(this->*process_function_list.front())();
				process_function_list.pop_front();
				list[i]->StatusOn();
			}
			if (count == time_tot) {
				all_process->StatusOn();
				button_run->SetButtonDefault();
				thread->quit();
			} else {
				return;
			}
		}
	}
}

void AutomationView::StartPumpAllChannel()
{	
	g_out << "StartPumpAllChannel\n";
	if (g_normal) {
		ShowSerialCodeInfo(reglo_icc->On(1));
		ShowSerialCodeInfo(reglo_icc->On(2));
	}
	g_out << '\n';
}

void AutomationView::StopPumpChannelNo2()
{
	g_out << "StopPumpChannelNo2\n";
	if (g_normal) {
		ShowSerialCodeInfo(reglo_icc->Off(2));
	}
	g_out << '\n';
}

void AutomationView::StartPulseGenerator()
{
	g_out << "StartPulseGenerator\n";
	if (g_normal) {
		ShowSerialCodeInfo(g1b->On());
	}
	g_out << '\n';
}

void AutomationView::StartPumpChannelNo2()
{
	g_out << "StartPumpChannelNo2\n";
	if (g_normal) {
		ShowSerialCodeInfo(reglo_icc->On(2));
	}
	g_out << '\n';
}

void AutomationView::StopPulseGenerator()
{
	g_out << "StopPulseGenerator\n";
	if (g_normal) {
		ShowSerialCodeInfo(g1b->Off());
	}
	g_out << '\n';
}

void AutomationView::StopPumpAllChannel()
{
	g_out << "StopPumpAllChannel\n";
	if (g_normal) {
		ShowSerialCodeInfo(reglo_icc->Off(1));
		ShowSerialCodeInfo(reglo_icc->Off(2));
	}
	g_out << '\n';
}

MetTreeData AutomationView::GetRpm()
{
	MetTreeData data = { 0.0f };
	if (reglo_icc) {
		for (int i = 0; i < PUMP_CHANNEL_COUNT; i++) {
			reglo_icc->GetRpm(data.value + i, i + 1);
		}
	} else {
		g_out << "fail to get rpm" << '\n';
	}
	return data;
}

MetTreeData AutomationView::GetDir()
{
	MetTreeData data = { 0.0f };
	bool dir[PUMP_CHANNEL_COUNT] = { false, false };
	if (reglo_icc) {
		for (int i = 0; i < PUMP_CHANNEL_COUNT; i++) {
			reglo_icc->GetDir(dir + i, i + 1);
		}
	} else {
		g_out << "fail to get dir" << '\n';
	}

	for (int i = 0; i < PUMP_CHANNEL_COUNT; i++) {
		if (dir[i]) {
			data.value[i] = 1.0f;
		} else {
			data.value[i] = 0.0f;
		}
	}
	return data;
}

MetTreeData AutomationView::GetFreq()
{
	MetTreeData data = { 0.0 };
	int freq = 0.0;
	if (g1b) {
		g1b->GetFreq(&freq);
	} else {
		g_out << "fail to get freq" << '\n';
	}
	data.value[0] = freq;
	return data;
}

MetTreeData AutomationView::GetPw()
{
	MetTreeData data = { 0.0f };
	if (g1b) {
		g1b->GetPulseWidth(data.value);
	} else {
		g_out << "fail to get pw" << '\n';
	}
	return data;
}

MetTreeData AutomationView::GetVoltage()
{
	MetTreeData data = { 0.0f };
	int voltage = 0;
	if (g1b) {
		g1b->GetVoltage(&voltage);
	} else {
		g_out << "fail to get voltage" << '\n';
	}
	data.value[0] = (float)(voltage);
	return data;
}

MetTreeData AutomationView::GetOffset()
{
	MetTreeData data = { 0.0f };
	int offset = 0;
	if (g1b) {
		g1b->GetOffset(&offset);
	} else {
		g_out << "fail to get offset" << '\n';
	}
	data.value[0] = (float)(offset);
	return data;
}

TimerWorker::TimerWorker(QWidget* parent)
{
	count = 0;
	timer = new QTimer(this);
	timer->setInterval(1000);
}

TimerWorker::~TimerWorker()
{

}

void TimerWorker::Reset()
{
	count = 0;
}

void TimerWorker::Start()
{
	connect(timer, &QTimer::timeout, this, &TimerWorker::Run);
	timer->start();
}

void TimerWorker::Finish()
{
	timer->stop();
}

void TimerWorker::Run()
{
	count += 1;
	emit TimeOut(count);
}