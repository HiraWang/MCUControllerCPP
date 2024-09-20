#include "g1b_view.h"

G1BView::G1BView(int w,
				 int h,
				 METParaList* para_list,
			     QWidget* parent) :
	w(w),
	h(h),
	para_list(para_list),
	QWidget(parent)
{
	setup_ui();

	std::string str = para_list->list[PUMP_KEYWORD].str;
	std::wstring wstring = std::wstring(str.begin(), str.end());
	LPCWSTR port = wstring.data();
	std::wcout << port << " " << sizeof(port) << '\n';
	std::wcout << L"COM4" << " " << sizeof(L"COM4") << '\n';

	G1B = new DeviceG1B(port,
				        CBR_9600,
				        8,
				        ONESTOPBIT,
				        NOPARITY);
	G1B->open();
}

G1BView::~G1BView()
{
	G1B->close();
}

void G1BView::setup_ui()
{
	setFixedWidth(w);
	setFixedHeight(h);

	METButtonStyle button_style;
	read_button = new METButton(button_style, "READ", "", 80, 80, "", "", this);
	connect(read_button, &QPushButton::released, this, &G1BView::read);

	write_button = new METButton(button_style, "WRITE", "", 80, 80, "", "", this);
	connect(write_button, &QPushButton::released, this, &G1BView::write);

	layout = new QHBoxLayout(this);
	layout->addWidget(read_button, 0, Qt::AlignCenter);
	layout->addWidget(write_button, 0, Qt::AlignCenter);
	setLayout(layout);
}

void G1BView::read()
{
	G1B->read();
}

void G1BView::write()
{
	G1B->write();
}