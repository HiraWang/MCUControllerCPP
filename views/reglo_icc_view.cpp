#include "reglo_icc_view.h"

#include "widgets/msg_subwindow.h"

RegloIccView::RegloIccView(int w,
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

	reglo_icc = new DeviceRegloIcc(port,
								   CBR_9600,
								   8,
								   ONESTOPBIT,
								   NOPARITY);
	if (reglo_icc->Open() != SERIAL_OK) {
		METMsgSubwindow("device RegloIcc open failed");
	}

	SetupUi();
}

RegloIccView::~RegloIccView()
{
	if (reglo_icc->Close() != SERIAL_OK) {
		METMsgSubwindow("device RegloIcc close failed");
	}
}

void RegloIccView::SetupUi()
{
	setFixedWidth(w);
	setFixedHeight(h);

	METButtonStyle button_style;
	read_button = new METButton(button_style, "READ", "", 80, 80, "", "", this);
	connect(read_button, &QPushButton::released, this, &RegloIccView::Read);

	write_button = new METButton(button_style, "WRITE", "", 80, 80, "", "", this);
	connect(write_button, &QPushButton::released, this, &RegloIccView::Write);

	layout = new QHBoxLayout(this);
	layout->addWidget(read_button, 0, Qt::AlignCenter);
	layout->addWidget(write_button, 0, Qt::AlignCenter);
	setLayout(layout);
}

void RegloIccView::Read()
{
	if (reglo_icc->Read() != SERIAL_OK) {
		METMsgSubwindow("device RegloIcc read failed");
	}
}

void RegloIccView::Write()
{
	if (reglo_icc->Write() != SERIAL_OK) {
		METMsgSubwindow("device RegloIcc write failed");
	}
}