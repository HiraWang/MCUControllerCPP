#include "utility.h"
#include "upper_view.h"
#include "widgets/style.h"

extern std::string IMAGE_MET_POWER;

UpperView::UpperView(QWidget* parent) :
	QWidget(parent)
{
	this->setup_ui();
}

UpperView::~UpperView()
{
	delete layout;
}

void a()
{
	std::cout << "a" << '\n';
}

void b()
{
	std::cout << "b" << '\n';
}

void UpperView::setup_ui()
{
	Style power_button_style(OFF_COLOR_1, ON_COLOR_1, OFF_COLOR_2, ON_COLOR_2,
		OFF_COLOR_3, ON_COLOR_3);
	power_button = new METButton("OFF", "ON", power_button_style, 80, 80, a, b,
		QString::fromStdString(get_image_abs_path(IMAGE_MET_POWER)),
		QString::fromStdString(get_image_abs_path(IMAGE_MET_POWER)));

	layout = new QHBoxLayout();
	layout->addWidget(power_button);
	setLayout(layout);
}