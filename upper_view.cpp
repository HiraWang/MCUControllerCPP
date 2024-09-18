#include "utility.h"
#include "upper_view.h"

extern std::string IMAGE_MET_EXIT;
extern std::string IMAGE_MET_FULL_SCREEN;
extern std::string IMAGE_MET_MAX_SIZE;
extern std::string IMAGE_MET_MENU;
extern std::string IMAGE_MET_POWER;

UpperView::UpperView(QWidget* parent) :
	QWidget(parent)
{
	setup_ui();
}

UpperView::~UpperView()
{
	delete layout;
}

void UpperView::setup_ui()
{
	METLabelStyle label_style(FONT_SIZE, COLOR_LIGHT_GRAY);
	label = new METLabel(label_style, "Device", 60, 25);

	METComboBoxStyle combo_box_style;
	combo_box = new METComboBox(combo_box_style, 250, 20);

	METButtonStyle button_style;
	exit_button = new METButton(button_style, "FULL", "MAX", 80, 80,
		QString::fromStdString(get_image_abs_path(IMAGE_MET_EXIT)),
		QString::fromStdString(get_image_abs_path(IMAGE_MET_EXIT)));
	window_button = new METButton(button_style, "EXIT", "", 80, 80,
		QString::fromStdString(get_image_abs_path(IMAGE_MET_FULL_SCREEN)),
		QString::fromStdString(get_image_abs_path(IMAGE_MET_MAX_SIZE)));
	menu_button = new METButton(button_style, "MENU", "", 80, 80,
		QString::fromStdString(get_image_abs_path(IMAGE_MET_MENU)),
		QString::fromStdString(get_image_abs_path(IMAGE_MET_MENU)));

	METButtonStyle power_button_style(OFF_COLOR_1, ON_COLOR_1, OFF_COLOR_2, ON_COLOR_2,
		OFF_COLOR_3, ON_COLOR_3);
	power_button = new METButton(power_button_style, "OFF", "ON", 80, 80,
		QString::fromStdString(get_image_abs_path(IMAGE_MET_POWER)),
		QString::fromStdString(get_image_abs_path(IMAGE_MET_POWER)));

	layout = new QHBoxLayout();
	layout->addWidget(label, 0, Qt::AlignTop | Qt::AlignLeft);
	layout->addWidget(combo_box, 0, Qt::AlignTop | Qt::AlignLeft);
	layout->addStretch(10);
	layout->addWidget(exit_button, 0, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(window_button, 0, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(menu_button, 0, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(power_button, 0, Qt::AlignTop | Qt::AlignRight);
	setLayout(layout);
}