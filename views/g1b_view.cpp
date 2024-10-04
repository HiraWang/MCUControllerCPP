#include "g1b_view.h"

#include "../widgets/color.h"
#include "../widgets/label.h"
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

	QWidget* container = new QWidget(this);
	container->setFixedWidth(600);
	container->setObjectName("g1b_container");
	container->setStyleSheet("QWidget#g1b_container {"
						     "background-color: " + QString(COLOR_GRAY) + ";"
						     "border: 2px solid black;"
						     "border-radius: 10px;"
						     "}");

	MetLabelStyle label_style(FONT_SIZE, FONT_COLOR);
	MetLabel* freq_label = new MetLabel(label_style, "Freq:", 200, 25, this);
	MetLabel* pw_label = new MetLabel(label_style, "Pulse Width:", 200, 25, this);
	MetLabel* voltage_label = new MetLabel(label_style, "Voltage:", 200, 25, this);
	MetLabel* offset_label = new MetLabel(label_style, "Offset:", 200, 25, this);
	MetLabel* out_label = new MetLabel(label_style, "Pulse State:", 200, 25, this);

	MetLineEditStyle line_edit_style;
	freq_edit = new MetLineEdit(line_edit_style, 100, 25, this);
	pw_edit = new MetLineEdit(line_edit_style, 100, 25, this);
	voltage_edit = new MetLineEdit(line_edit_style, 100, 25, this);
	offset_edit = new MetLineEdit(line_edit_style, 100, 25, this);

	MetLabel* freq_unit = new MetLabel(label_style, "Hz", 120, 25, this);
	MetLabel* pw_unit = new MetLabel(label_style, "us", 120, 25, this);
	MetLabel* voltage_unit = new MetLabel(label_style, "V", 120, 25, this);
	MetLabel* offset_unit = new MetLabel(label_style, "V", 120, 25, this);

	MetButtonStyle button_style;
	freq_button = new MetButton(button_style, "SET", "SET", 80, 25, "", "", this);
	pw_button = new MetButton(button_style, "SET", "SET", 80, 25, "", "", this);
	voltage_button = new MetButton(button_style, "SET", "SET", 80, 25, "", "", this);
	offset_button = new MetButton(button_style, "SET", "SET", 80, 25, "", "", this);

	MetButtonStyle two_state_button_style(OFF_COLOR_1, ON_COLOR_1, OFF_COLOR_2,
		ON_COLOR_2, OFF_COLOR_3, ON_COLOR_3);
	out_button = new MetButton(two_state_button_style, "", "", 80, 25, "", "", this);

	QHBoxLayout* freq_layout = new QHBoxLayout();
	freq_layout->addWidget(freq_label, 0, Qt::AlignLeft);
	freq_layout->addWidget(freq_edit, 0, Qt::AlignCenter);
	freq_layout->addWidget(freq_unit, 0, Qt::AlignLeft);
	freq_layout->addWidget(freq_button, 0, Qt::AlignRight);

	QHBoxLayout* pw_layout = new QHBoxLayout();
	pw_layout->addWidget(pw_label, 0, Qt::AlignLeft);
	pw_layout->addWidget(pw_edit, 0, Qt::AlignCenter);
	pw_layout->addWidget(pw_unit, 0, Qt::AlignLeft);
	pw_layout->addWidget(pw_button, 0, Qt::AlignRight);

	QHBoxLayout* voltage_layout = new QHBoxLayout();
	voltage_layout->addWidget(voltage_label, 0, Qt::AlignLeft);
	voltage_layout->addWidget(voltage_edit, 0, Qt::AlignCenter);
	voltage_layout->addWidget(voltage_unit, 0, Qt::AlignLeft);
	voltage_layout->addWidget(voltage_button, 0, Qt::AlignRight);

	QHBoxLayout* offset_layout = new QHBoxLayout();
	offset_layout->addWidget(offset_label, 0, Qt::AlignLeft);
	offset_layout->addWidget(offset_edit, 0, Qt::AlignCenter);
	offset_layout->addWidget(offset_unit, 0, Qt::AlignLeft);
	offset_layout->addWidget(offset_button, 0, Qt::AlignRight);

	QHBoxLayout* out_layout = new QHBoxLayout();
	out_layout->addWidget(out_label, 0, Qt::AlignLeft);
	out_layout->addWidget(out_button, 0, Qt::AlignRight);

	QVBoxLayout* container_layout = new QVBoxLayout();
	container_layout->addItem(freq_layout);
	container_layout->addItem(pw_layout);
	container_layout->addItem(voltage_layout);
	container_layout->addItem(offset_layout);
	container_layout->addItem(out_layout);
	container->setLayout(container_layout);

	layout = new QVBoxLayout(this);
	layout->addWidget(container, 0, Qt::AlignCenter);
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