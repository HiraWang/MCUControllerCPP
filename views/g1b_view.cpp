#include "g1b_view.h"

#include "../widgets/login_subwindow.h"
#include "../widgets/msg_subwindow.h"

G1BView::G1BView(int w,
				 int h,
				 MetParaList* para_list,
			     QWidget* parent) :
	w(w),
	h(h),
	para_list(para_list),
	serial_status(SERIAL_OK),
	QWidget(parent)
{
	std::string str = para_list->list[PULSE_GEN_KEYWORD].str;
	std::wstring wstring = std::wstring(str.begin(), str.end());
	LPCWSTR port = wstring.data();
	std::wcout << port << " " << sizeof(port) << '\n';
	std::wcout << L"COM4" << " " << sizeof(L"COM4") << '\n';

	g1b = new DeviceG1B(port,
				        CBR_9600,
				        8,
				        ONESTOPBIT,
				        NOPARITY);

	serial_status = g1b->Open();
	if (serial_status != SERIAL_OK) {
		MetMsgSubwindow("device G1B open failed");
	} else {
		std::cout << "device G1B opened" << '\n';
		QString account = QString::fromStdString(para_list->list[PULSE_GEN_ID].str);
		QString password = QString::fromStdString(para_list->list[PULSE_GEN_PASSWORD].str);
		MetLoginSubwindow(g1b, account, password, this);
	}
}

G1BView::~G1BView()
{
	if (g1b->Close() != SERIAL_OK) {
		MetMsgSubwindow("device G1B close failed");
	}
}

void G1BView::SetupUi()
{
	setFixedWidth(w);
	setFixedHeight(h);

	MetButtonStyle button_style;
	read_button = new MetButton(button_style, "READ", "", 80, 80, "", "", this);
	connect(read_button, &QPushButton::released, this, &G1BView::Read);

	write_button = new MetButton(button_style, "WRITE", "", 80, 80, "", "", this);
	connect(write_button, &QPushButton::released, this, &G1BView::Write);

	layout = new QHBoxLayout(this);
	layout->addWidget(read_button, 0, Qt::AlignCenter);
	layout->addWidget(write_button, 0, Qt::AlignCenter);
	setLayout(layout);
}

void G1BView::SetSerialStatusOk()
{
	serial_status = SERIAL_OK;
}

void G1BView::SetSerialStatusFail()
{
	serial_status = SERIAL_FAIL;
}

void G1BView::Read()
{
	if (g1b->Read() != SERIAL_OK) {
		MetMsgSubwindow("device G1B read failed");
	}
}

void G1BView::Write()
{
	if (g1b->Write() != SERIAL_OK) {
		MetMsgSubwindow("device G1B write failed");
	}
}