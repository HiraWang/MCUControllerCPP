#include <QStyleOption>
#include <QPainter>

#include "utility.h"
#include "upper_view.h"

extern std::string IMAGE_MET_POWER;
extern std::string IMAGE_MET_MAX_SIZE;
extern std::string IMAGE_MET_FULL_SCREEN;

UpperView::UpperView(QWidget* parent) :
	QWidget(parent)
{
	this->setup_ui();
}

UpperView::~UpperView()
{
	delete layout;
}

void UpperView::setup_ui()
{
	METLabelStyle label_style;
	label = new METLabel(label_style, "Device", 60, 25);

	METComboBoxStyle combo_box_style;
	combo_box = new METComboBox(combo_box_style, 250, 20);

	METButtonStyle button_style;
	window_button = new METButton(button_style, "FULL", "MAX", 80, 80,
		QString::fromStdString(get_image_abs_path(IMAGE_MET_FULL_SCREEN)),
		QString::fromStdString(get_image_abs_path(IMAGE_MET_MAX_SIZE)));

	METButtonStyle power_button_style(OFF_COLOR_1, ON_COLOR_1, OFF_COLOR_2, ON_COLOR_2,
		OFF_COLOR_3, ON_COLOR_3);
	power_button = new METButton(power_button_style, "OFF", "ON", 80, 80,
		QString::fromStdString(get_image_abs_path(IMAGE_MET_POWER)),
		QString::fromStdString(get_image_abs_path(IMAGE_MET_POWER)));

	layout = new QHBoxLayout();
	layout->addWidget(label, 0, Qt::AlignTop | Qt::AlignLeft);
	layout->addWidget(combo_box, 0, Qt::AlignTop | Qt::AlignLeft);
	layout->addStretch(10);
	layout->addWidget(window_button, 0, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(power_button, 0, Qt::AlignTop | Qt::AlignRight);
	setLayout(layout);
}