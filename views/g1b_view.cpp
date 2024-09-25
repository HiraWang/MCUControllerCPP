#include "g1b_view.h"

#include "widgets/msg_subwindow.h"

G1BView::G1BView(int w,
				 int h,
				 METParaList* para_list,
			     QWidget* parent) :
	w(w),
	h(h),
	para_list(para_list),
	QWidget(parent)
{
	std::string str = para_list->list[PULSE_GEN_KEYWORD].str;
	std::wstring wstring = std::wstring(str.begin(), str.end());
	LPCWSTR port = wstring.data();
	std::wcout << port << " " << sizeof(port) << '\n';
	std::wcout << L"COM4" << " " << sizeof(L"COM4") << '\n';

	G1B = new DeviceG1B(port,
				        CBR_9600,
				        8,
				        ONESTOPBIT,
				        NOPARITY);
	if (G1B->Open() != SERIAL_OK) {
		METMsgSubwindow("device G1B open failed");
	}

	SetupUi();
}

G1BView::~G1BView()
{
	if (G1B->Close() != SERIAL_OK) {
		METMsgSubwindow("device G1B close failed");
	}
}

void G1BView::SetupUi()
{
	setFixedWidth(w);
	setFixedHeight(h);

	METButtonStyle button_style;
	read_button = new METButton(button_style, "READ", "", 80, 80, "", "", this);
	connect(read_button, &QPushButton::released, this, &G1BView::Read);

	write_button = new METButton(button_style, "WRITE", "", 80, 80, "", "", this);
	connect(write_button, &QPushButton::released, this, &G1BView::Write);

	layout = new QHBoxLayout(this);
	layout->addWidget(read_button, 0, Qt::AlignCenter);
	layout->addWidget(write_button, 0, Qt::AlignCenter);
	setLayout(layout);
}

void G1BView::Read()
{
	if (G1B->Read() != SERIAL_OK) {
		METMsgSubwindow("device G1B read failed");
	}
}

void G1BView::Write()
{
	if (G1B->Write() != SERIAL_OK) {
		METMsgSubwindow("device G1B write failed");
	}
}