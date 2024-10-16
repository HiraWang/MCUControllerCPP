#include "monitor_view.h"

#include <direct.h>
#include <QGridLayout>

#include "../widgets/button.h"
#include "../widgets/login_subwindow.h"
#include "../widgets/msg_subwindow.h"

extern bool g_ui_test;
extern std::string IMAGE_MET_LEFT;
extern std::string IMAGE_MET_RIGHT;
extern std::string IMAGE_MET_UP;
extern std::string IMAGE_MET_DOWN;
extern std::string IMAGE_MET_ATTACHED_FILES;
extern std::string IMAGE_MET_IMAGE;
extern std::string IMAGE_MET_LOAD;
extern std::string IMAGE_MET_MENU;
extern std::string IMAGE_MET_RESULT;
extern std::string IMAGE_MET_SCAN;
extern std::string IMAGE_MET_STOP;
extern std::string MONITOR_BUFFER_DIR;
extern std::string MONITOR_RESULT_DIR;

MonitorView::MonitorView(int w,
					     int h,
					     MetParaList* para_list,
					     QWidget* parent) :
	w(w),
	h(h),
	upper_widget_h(120),
	scale_x_interval(0.5f),
	scale_y_interval(0.2f),
	para_list(para_list),
	serial_status(SERIAL_OK),
	QWidget(parent)
{
	if (g_ui_test) {
		serial_status = SERIAL_OK;
		due = nullptr;
		SetupUi();
		return;
	}

	std::string str = para_list->list[MONITOR_KEYWORD].str;
	std::wstring wstring = std::wstring(str.begin(), str.end());
	LPCWSTR port = wstring.data();
	std::wcout << port << " " << sizeof(port) << '\n';

	due = new DeviceArduinoDue(port,
							   CBR_9600,
							   8,
							   ONESTOPBIT,
							   NOPARITY);
	serial_status = due->Open();

	if (serial_status != SERIAL_OK) {
		MetMsgSubwindow("monitor open failed");
		due = nullptr;
		return;
	} else {
		std::cout << "monitor opened" << '\n';
		due->activate = false;
		SetupUi();
	}
}

MonitorView::~MonitorView()
{
	if (due && due->Close() != SERIAL_OK) {
		MetMsgSubwindow("device Due close failed");
	}
}

void MonitorView::SetupUi()
{
	setFixedWidth(w);
	setFixedHeight(h);

	helper = new Helper(HelperType::OSCILLOSCOPE);
	helper->InitOscilloscopeInfo(para_list->list[OFFSET].num, 1000.0f, 0.0f);
	canvas = new MetCanvas(helper, width(), height() - upper_widget_h, this);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &MonitorView::Update);

	MetButtonStyle button_style;
	scan_button = new MetButton(button_style, "", "", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_SCAN)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_STOP)), this);
	scale_reset_button = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)), this);
	scale_x_plus_button = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_RIGHT)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_RIGHT)), this);
	scale_y_plus_button = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_UP)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_UP)), this);
	scale_x_minus_button = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_LEFT)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_LEFT)), this);
	scale_y_minus_button = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_DOWN)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_DOWN)), this);
	plot_info_button = new MetButton(button_style, "", "", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_MENU)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_MENU)), this);
	render_button = new MetButton(button_style, "", "", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_IMAGE)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_IMAGE)), this);
	buffer_dir_button = new MetButton(button_style, "", "", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_ATTACHED_FILES)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_ATTACHED_FILES)), this);
	result_dir_button = new MetButton(button_style, "", "", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_RESULT)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_RESULT)), this);

	connect(scan_button, &QPushButton::released, this,
		&MonitorView::ToggleScanButton);
	connect(scale_reset_button, &QPushButton::released, this,
		&MonitorView::ToggleScaleResetButton);
	connect(scale_x_plus_button, &QPushButton::released, this,
		&MonitorView::ToggleScaleXPlusButton);
	connect(scale_y_plus_button, &QPushButton::released, this,
		&MonitorView::ToggleScaleYPlusButton);
	connect(scale_x_minus_button, &QPushButton::released, this,
		&MonitorView::ToggleScaleXMinusButton);
	connect(scale_y_minus_button, &QPushButton::released, this,
		&MonitorView::ToggleScaleYMinusButton);
	connect(plot_info_button, &QPushButton::released, this,
		&MonitorView::TogglePlotInfoButton);
	connect(render_button, &QPushButton::released, this,
		&MonitorView::ToggleRenderButton);
	connect(buffer_dir_button, &QPushButton::released, this,
		&MonitorView::ToggleBufferDirButton);
	connect(result_dir_button, &QPushButton::released, this,
		&MonitorView::ToggleResultDirButton);

	MetSliderStyle slider_style(COLOR_WHITE, COLOR_BLACK);
	data_offset_slider = new MetSlider(slider_style,Qt::Vertical,
		10, 76, 0, 24, 1, this);
	data_offset_slider->setValue(para_list->list[OFFSET].num);
	data_offset_slider->setSliderPosition(para_list->list[OFFSET].num);

	connect(data_offset_slider, &QSlider::valueChanged, this,
		&MonitorView::ToggleDataOffsetSlider);
	
	QWidget* scale_buttons = new QWidget(this);
	scale_buttons->setFixedWidth(100);
	scale_buttons->setFixedHeight(100);
	QGridLayout* scale_layout = new QGridLayout();
	scale_layout->addWidget(scale_x_minus_button, 1, 0, Qt::AlignCenter);
	scale_layout->addWidget(scale_x_plus_button, 1, 2, Qt::AlignCenter);
	scale_layout->addWidget(scale_reset_button, 1, 1, Qt::AlignCenter);
	scale_layout->addWidget(scale_y_minus_button, 2, 1, Qt::AlignCenter);
	scale_layout->addWidget(scale_y_plus_button, 0, 1, Qt::AlignCenter);
	scale_layout->setContentsMargins(11, 9, 11, 11);
	scale_buttons->setLayout(scale_layout);

	QWidget* upper_widgets = new QWidget(this);
	upper_widgets->setFixedHeight(upper_widget_h - 20);
	QHBoxLayout* upper_layout = new QHBoxLayout();
	upper_layout->addWidget(scan_button, 0, Qt::AlignLeft);
	upper_layout->addWidget(plot_info_button, 0, Qt::AlignLeft);
	upper_layout->addWidget(render_button, 0, Qt::AlignLeft);
	upper_layout->addWidget(buffer_dir_button, 0, Qt::AlignLeft);
	upper_layout->addWidget(result_dir_button, 0, Qt::AlignLeft);
	upper_layout->addWidget(data_offset_slider, 0, Qt::AlignLeft);
	upper_layout->addWidget(scale_buttons, 0, Qt::AlignLeft);
	upper_layout->addStretch(10);
	upper_layout->setContentsMargins(0, 0, 0, 0);
	upper_widgets->setLayout(upper_layout);

	layout = new QVBoxLayout(this);
	layout->addWidget(upper_widgets, 0, Qt::AlignTop);
	layout->addWidget(canvas, 0, Qt::AlignBottom);
	layout->addStretch(1);
	setLayout(layout);
}

void MonitorView::Update()
{
	helper->SetCount(due->count);
	canvas->update();
}

void MonitorView::ScaleUpCanvasSize()
{
	canvas->setFixedSize(QSize(width(), height() - upper_widget_h));
	canvas->update();
}

void MonitorView::ScaleDownCanvasSize()
{
	canvas->setFixedSize(QSize(width(), height() - upper_widget_h - 23));
	canvas->update();
}

void MonitorView::ToggleScanButton()
{
	if (scan_button->status) {
		scan_button->SetButtonDefault();
		due->activate = false;
		thread->join();
		timer->stop();
	} else {
		scan_button->SetButtonPressed();
		_mkdir(MONITOR_RESULT_DIR.c_str());
		RemoveAllFilesFromDir(MONITOR_RESULT_DIR.c_str());
		helper->SetDataMinAndMax(1000.0f, 0.0f);
		helper->SetFirstRoundFlag(true);
		due->activate = true;
		thread = new std::thread(&DeviceArduinoDue::ReadBufferAndSave, due);
		timer->start(10);
	}
}

void MonitorView::ToggleScaleResetButton()
{
	scale_reset_button->SetButtonDefault();
	helper->SetScaleX(1.0f);
	helper->SetScaleY(1.0f);
	canvas->update();
}

void MonitorView::ToggleScaleXPlusButton()
{
	scale_x_plus_button->SetButtonDefault();
	float scale_x = helper->GetScaleX();
	scale_x += scale_x_interval;

	if (1.0f <= scale_x && scale_x < 10.0f) {
		helper->SetScaleX(scale_x);
		canvas->update();
	}
}

void MonitorView::ToggleScaleYPlusButton()
{
	scale_y_plus_button->SetButtonDefault();
	float scale_y = helper->GetScaleY();
	scale_y += scale_y_interval;

	if (0.0f < scale_y && scale_y < 100.0f) {
		helper->SetScaleY(scale_y);
		canvas->update();
	}
}

void MonitorView::ToggleScaleXMinusButton()
{
	scale_x_plus_button->SetButtonDefault();
	float scale_x = helper->GetScaleX();
	scale_x -= scale_x_interval;

	if (1.0f <= scale_x && scale_x < 10.0f) {
		helper->SetScaleX(scale_x);
		canvas->update();
	}
}

void MonitorView::ToggleScaleYMinusButton()
{
	scale_y_plus_button->SetButtonDefault();
	float scale_y = helper->GetScaleY();
	scale_y -= scale_y_interval;

	if (scale_y_interval <= scale_y && scale_y < 100.0f) {
		helper->SetScaleY(scale_y);
		canvas->update();
	}
}

void MonitorView::TogglePlotInfoButton()
{
	if (plot_info_button->status) {
		plot_info_button->SetButtonDefault();
		helper->SetPlotInfoFlag(true);
	} else {
		plot_info_button->SetButtonPressed();
		helper->SetPlotInfoFlag(false);
	}
}

void MonitorView::ToggleRenderButton()
{
	render_button->SetButtonDefault();
	canvas->SetRenderFlag(true);
}

void MonitorView::ToggleBufferDirButton()
{
	buffer_dir_button->SetButtonDefault();
	std::wstring result_dir = std::wstring(MONITOR_BUFFER_DIR.begin(), MONITOR_BUFFER_DIR.end());
	ShellExecute(nullptr, L"open", nullptr, nullptr, result_dir.c_str(), SW_SHOWNORMAL);
}

void MonitorView::ToggleResultDirButton()
{
	buffer_dir_button->SetButtonDefault();
	std::wstring result_dir = std::wstring(MONITOR_RESULT_DIR.begin(), MONITOR_RESULT_DIR.end());
	ShellExecute(nullptr, L"open", nullptr, nullptr, result_dir.c_str(), SW_SHOWNORMAL);
}

void MonitorView::ToggleDataOffsetSlider()
{
	if (data_offset_slider->value() == 0) {
		helper->SetDataOffset(1);
	} else {
		helper->SetDataOffset(data_offset_slider->value());
	}
}