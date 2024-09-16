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
	METButtonStyle button_style;
	METButtonStyle power_button_style(OFF_COLOR_1, ON_COLOR_1, OFF_COLOR_2, ON_COLOR_2,
		OFF_COLOR_3, ON_COLOR_3);

	window_button = new METButton("FULL", "MAX", button_style, 80, 80,
		QString::fromStdString(get_image_abs_path(IMAGE_MET_FULL_SCREEN)),
		QString::fromStdString(get_image_abs_path(IMAGE_MET_MAX_SIZE)));
	power_button = new METButton("OFF", "ON", power_button_style, 80, 80,
		QString::fromStdString(get_image_abs_path(IMAGE_MET_POWER)),
		QString::fromStdString(get_image_abs_path(IMAGE_MET_POWER)));

	layout = new QHBoxLayout();
	layout->addWidget(window_button, 0, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(power_button, 0, Qt::AlignTop | Qt::AlignRight);
	setLayout(layout);
}