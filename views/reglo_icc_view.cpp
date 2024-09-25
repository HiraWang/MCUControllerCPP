#include "reglo_icc_view.h"

#include "widgets/msg_subwindow.h"

RegloIccView::RegloIccView(int w,
						   int h,
						   MetParaList* para_list,
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

	reglo_icc = new DeviceRegloIcc(port,
								   CBR_9600,
								   8,
								   ONESTOPBIT,
								   NOPARITY);
	if (reglo_icc->Open() != SERIAL_OK) {
		MetMsgSubwindow("device RegloIcc open failed");
	}

	SetupUi();
}

RegloIccView::~RegloIccView()
{
	if (reglo_icc->Close() != SERIAL_OK) {
		MetMsgSubwindow("device RegloIcc close failed");
	}
}

void RegloIccView::SetupUi()
{
	setFixedWidth(w);
	setFixedHeight(h);

	MetPumpChannelStyle pump_channel_style;
	channel_1 = new MetPumpChannel(pump_channel_style, reglo_icc,
		1, "Channel 1", this);
	channel_2 = new MetPumpChannel(pump_channel_style, reglo_icc,
		2, "Channel 2", this);

	layout = new QVBoxLayout(this);
	layout->addWidget(channel_1, 0, Qt::AlignCenter);
	layout->addWidget(channel_2, 0, Qt::AlignCenter);
	setLayout(layout);
}

void RegloIccView::Read()
{
	if (reglo_icc->Read() != SERIAL_OK) {
		MetMsgSubwindow("device RegloIcc read failed");
	}
}

void RegloIccView::Write()
{
	if (reglo_icc->Write() != SERIAL_OK) {
		MetMsgSubwindow("device RegloIcc write failed");
	}
}