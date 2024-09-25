#include "upper_view.h"

extern std::string IMAGE_MET_CLOSE;
extern std::string IMAGE_MET_EXIT;
extern std::string IMAGE_MET_FULL_SCREEN;
extern std::string IMAGE_MET_LOAD;
extern std::string IMAGE_MET_MAX_SIZE;
extern std::string IMAGE_MET_MENU;
extern std::string IMAGE_MET_POWER;

UpperView::UpperView(QWidget* parent) :
	QWidget(parent)
{
	SetupUi();
}

UpperView::~UpperView()
{

}

void UpperView::SetupUi()
{
	METLabelStyle label_style(FONT_SIZE, COLOR_LIGHT_GRAY);
	label = new METLabel(label_style, "Device", 60, 25, this);

	METComboBoxStyle combo_box_style;
	combo_box = new METComboBox(combo_box_style, 250, 20, this);

	METButtonStyle button_style;
	exit_button = new METButton(button_style, "FULL", "MAX", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_EXIT)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_EXIT)), this);
	window_button = new METButton(button_style, "EXIT", "", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_FULL_SCREEN)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_MAX_SIZE)), this);
	load_config_button = new METButton(button_style, "LOAD", "", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_LOAD)), this);
	menu_button = new METButton(button_style, "MENU", "CLOSE", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_MENU)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_CLOSE)), this);

	METButtonStyle power_button_style(OFF_COLOR_1, ON_COLOR_1, OFF_COLOR_2, ON_COLOR_2,
		OFF_COLOR_3, ON_COLOR_3);
	power_button = new METButton(power_button_style, "OFF", "ON", 80, 80,
		QString::fromStdString(GetAbsPath(IMAGE_MET_POWER)),
		QString::fromStdString(GetAbsPath(IMAGE_MET_POWER)), this);

	layout = new QHBoxLayout(this);
	layout->addWidget(label, 0, Qt::AlignTop | Qt::AlignLeft);
	layout->addWidget(combo_box, 0, Qt::AlignTop | Qt::AlignLeft);
	layout->addStretch(10);
	layout->addWidget(exit_button, 0, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(window_button, 0, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(load_config_button, 0, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(menu_button, 0, Qt::AlignTop | Qt::AlignRight);
	layout->addWidget(power_button, 0, Qt::AlignTop | Qt::AlignRight);
	setLayout(layout);
}