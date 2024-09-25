#include "pump_channel_view.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>

#include "../widgets/label.h"
#include "../widgets/line_edit.h"

MetPumpChannel::MetPumpChannel(MetPumpChannelStyle met_style,
							   DeviceRegloIcc* reglo_icc,
							   int channel,
							   QString name,
							   QWidget* parent) :
	met_style(met_style),
	reglo_icc(reglo_icc),
	channel(channel),
	name(name),
	QWidget(parent)
{
	LoadStyleSheet();
	SetupUi();
}

MetPumpChannel::~MetPumpChannel()
{

}

void MetPumpChannel::paintEvent(QPaintEvent* pe)
{
	QStyleOption o;
	o.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void MetPumpChannel::SetupUi()
{
	setFixedWidth(500);
	setStyleSheet(style_sheet);

	MetLabelStyle label_style(FONT_SIZE, FONT_COLOR);
	MetLabel* name_label = new MetLabel(label_style, name, 120, 25, this);
	MetLabel* rpm_label = new MetLabel(label_style, "Rate:", 120, 25, this);
	MetLabel* dir_label = new MetLabel(label_style, "Direction:", 120, 25, this);
	MetLabel* out_label = new MetLabel(label_style, "Pump State:", 120, 25, this);

	MetLineEditStyle line_edit_style;
	rpm_edit = new MetLineEdit(line_edit_style, 100, 25, this);

	MetButtonStyle button_style;
	rpm_button = new MetButton(button_style, "SET", "SET", 80, 25, "", "", this);
	
	MetButtonStyle two_state_button_style(OFF_COLOR_1, ON_COLOR_1, OFF_COLOR_2,
		ON_COLOR_2, OFF_COLOR_3, ON_COLOR_3);
	dir_button = new MetButton(two_state_button_style, "", "", 80, 25, "", "", this);
	out_button = new MetButton(two_state_button_style, "", "", 80, 25, "", "", this);

	connect(rpm_button, &QPushButton::released, this,
		&MetPumpChannel::ToggleRpmButton);
	connect(dir_button, &QPushButton::released, this,
		&MetPumpChannel::ToggleDirButton);
	connect(out_button, &QPushButton::released, this,
		&MetPumpChannel::ToggleOutButton);

	QHBoxLayout* rpm_layout = new QHBoxLayout();
	rpm_layout->addWidget(rpm_label, 0, Qt::AlignLeft);
	rpm_layout->addWidget(rpm_edit, 0, Qt::AlignCenter);
	rpm_layout->addWidget(rpm_button, 0, Qt::AlignRight);

	QHBoxLayout* dir_layout = new QHBoxLayout();
	dir_layout->addWidget(dir_label, 0, Qt::AlignLeft);
	dir_layout->addWidget(dir_button, 0, Qt::AlignRight);

	QHBoxLayout* out_layout = new QHBoxLayout();
	out_layout->addWidget(out_label, 0, Qt::AlignLeft);
	out_layout->addWidget(out_button, 0, Qt::AlignRight);

	layout = new QVBoxLayout(this);
	layout->addWidget(name_label, 0, Qt::AlignCenter);
	layout->addItem(rpm_layout);
	layout->addItem(dir_layout);
	layout->addItem(out_layout);
	setLayout(layout);
}

void MetPumpChannel::LoadStyleSheet()
{
	style_sheet =
		"MetPumpChannel {"
		"background-color: " + met_style.bkg_color + ";"
		"border: 2px solid black;"
		"border-radius: 10px;"
		"}";
}

void MetPumpChannel::ToggleRpmButton()
{
	rpm_button->SetButtonDefault();
}

void MetPumpChannel::ToggleDirButton()
{
	if (dir_button->status) {
		dir_button->SetButtonDefault();
	} else {
		dir_button->SetButtonPressed();
	}
}

void MetPumpChannel::ToggleOutButton()
{
	if (out_button->status) {
		out_button->SetButtonDefault();
	} else {
		out_button->SetButtonPressed();
	}
}

MetPumpChannelStyle::MetPumpChannelStyle(QString bkg_color,
										 QString font_size,
										 QString font_color) :
	bkg_color(bkg_color),
	font_size(font_size),
	font_color(font_color)
{

}

MetPumpChannelStyle::~MetPumpChannelStyle()
{

}