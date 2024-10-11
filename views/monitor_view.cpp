#include "monitor_view.h"

#include <QTimer>

#include "../widgets/login_subwindow.h"
#include "../widgets/msg_subwindow.h"

extern bool g_ui_test;

MonitorView::MonitorView(int w,
					     int h,
					     MetParaList* para_list,
					     QWidget* parent) :
	w(w),
	h(h),
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
	helper->Init(0, 0, 0, 0);
	canvas = new MetCanvas(helper, width() - 100, height() - 100, this);

	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, canvas, &MetCanvas::animate);
	timer->start(50);

	layout = new QVBoxLayout(this);
	layout->addWidget(canvas, 0, Qt::AlignCenter);
	layout->setContentsMargins(15, 15, 15, 15);
	setLayout(layout);
}