#include "monitor_view.h"

#include <QTimer>
#include <QGridLayout>

#include "../widgets/button.h"
#include "../widgets/login_subwindow.h"
#include "../widgets/msg_subwindow.h"

extern bool g_ui_test;
extern std::string IMAGE_MET_LOAD;
extern std::string IMAGE_MET_LEFT;
extern std::string IMAGE_MET_RIGHT;
extern std::string IMAGE_MET_UP;
extern std::string IMAGE_MET_DOWN;

MonitorView::MonitorView(int w,
					     int h,
					     MetParaList* para_list,
					     QWidget* parent) :
	w(w),
	h(h),
	scale_x_interval(0.5f),
	scale_y_interval(0.2f),
	para_list(para_list),
	serial_status(SERIAL_OK),
	QWidget(parent)
{
	if (g_ui_test) {
		serial_status = SERIAL_OK;
		SetupUi();
		return;
	}

	if (serial_status != SERIAL_OK) {
		MetMsgSubwindow("monitor open failed");
		return;
	}
	else {
		std::cout << "monitor opened" << '\n';
		SetupUi();
	}
}

MonitorView::~MonitorView()
{

}

void MonitorView::SetupUi()
{
	setFixedWidth(w);
	setFixedHeight(h);

	helper = new Helper(HelperType::OSCILLOSCOPE);
	helper->SetScaleX(1.0f);
	helper->SetScaleY(1.0f);
	canvas = new MetCanvas(helper, width(), height() - 100, this);

	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, canvas, &MetCanvas::animate);
	timer->start(50);

	MetButtonStyle button_style;
	scale_reset = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)), this);
	scale_x_plus = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_RIGHT)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_RIGHT)), this);
	scale_y_plus = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_UP)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_UP)), this);
	scale_x_minus = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_LEFT)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_LEFT)), this);
	scale_y_minus = new MetButton(button_style, "", "", 25, 25,
		QString::fromStdString(GetAbsPath(IMAGE_MET_DOWN)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_DOWN)), this);

	connect(scale_reset, &QPushButton::released, this,
		&MonitorView::ToggleScaleResetButton);
	connect(scale_x_plus, &QPushButton::released, this,
		&MonitorView::ToggleScaleXPlusButton);
	connect(scale_y_plus, &QPushButton::released, this,
		&MonitorView::ToggleScaleYPlusButton);
	connect(scale_x_minus, &QPushButton::released, this,
		&MonitorView::ToggleScaleXMinusButton);
	connect(scale_y_minus, &QPushButton::released, this,
		&MonitorView::ToggleScaleYMinusButton);

	QWidget* scale_buttons = new QWidget(this);
	scale_buttons->setFixedWidth(100);
	scale_buttons->setFixedHeight(100);

	QGridLayout* scale_layout = new QGridLayout();
	scale_layout->addWidget(scale_x_minus, 1, 0, Qt::AlignCenter);
	scale_layout->addWidget(scale_x_plus, 1, 2, Qt::AlignCenter);
	scale_layout->addWidget(scale_reset, 1, 1, Qt::AlignCenter);
	scale_layout->addWidget(scale_y_minus, 2, 1, Qt::AlignCenter);
	scale_layout->addWidget(scale_y_plus, 0, 1, Qt::AlignCenter);
	scale_buttons->setLayout(scale_layout);

	QHBoxLayout* upper_layout = new QHBoxLayout();
	upper_layout->addWidget(scale_buttons, 0, Qt::AlignLeft);

	layout = new QVBoxLayout(this);
	layout->addItem(upper_layout);
	layout->addWidget(canvas, 0, Qt::AlignBottom);
	layout->setContentsMargins(6, 0, 0, 0);
	setLayout(layout);
}

void MonitorView::ToggleScaleResetButton()
{
	scale_reset->SetButtonDefault();
	helper->SetScaleX(1.0f);
	helper->SetScaleY(1.0f);
	canvas->update();
}

void MonitorView::ToggleScaleXPlusButton()
{
	scale_x_plus->SetButtonDefault();
	float scale_x = helper->GetScaleX();
	scale_x += scale_x_interval;

	if (1.0f <= scale_x && scale_x < 10.0f) {
		helper->SetScaleX(scale_x);
		canvas->update();
	}
}

void MonitorView::ToggleScaleYPlusButton()
{
	scale_y_plus->SetButtonDefault();
	float scale_y = helper->GetScaleY();
	scale_y += scale_y_interval;

	if (0.0f < scale_y && scale_y < 10.0f) {
		helper->SetScaleY(scale_y);
		canvas->update();
	}
}

void MonitorView::ToggleScaleXMinusButton()
{
	scale_x_plus->SetButtonDefault();
	float scale_x = helper->GetScaleX();
	scale_x -= scale_x_interval;

	if (1.0f <= scale_x && scale_x < 10.0f) {
		helper->SetScaleX(scale_x);
		canvas->update();
	}
}

void MonitorView::ToggleScaleYMinusButton()
{
	scale_y_plus->SetButtonDefault();
	float scale_y = helper->GetScaleY();
	scale_y -= scale_y_interval;

	if (0.0f < scale_y && scale_y < 10.0f) {
		helper->SetScaleY(scale_y);
		canvas->update();
	}
}