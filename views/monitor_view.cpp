#include "monitor_view.h"

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

	layout = new QVBoxLayout(this);
	setLayout(layout);
}