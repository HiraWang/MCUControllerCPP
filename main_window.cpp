#include "main_window.h"

#include <QPainter>
#include <QStyleOption>

#include "devices/device.h"
#include "views/g1b_view.h"
#include "views/reglo_icc_view.h"
#include "widgets/msg_subwindow.h"

MainWindow::MainWindow(QWidget* parent) : 
    QMainWindow(parent), // call superclass constructor with an argument
    ui(new MainWindowUI()),
	para_list(new MetParaList())
{
	// set main window ui
    ui->SetupUi(this);

	// connet widgets with main window callback functions 
	connect(ui->upper_view->exit_button, &QPushButton::released,
		this, &MainWindow::ToggleExitButton);
	connect(ui->upper_view->window_button, &QPushButton::released,
		this, &MainWindow::ToggleWindowButton);
	connect(ui->upper_view->load_config_button, &QPushButton::released,
		this, &MainWindow::ToggleLoadConfigButton);
	connect(ui->upper_view->menu_button, &QPushButton::released,
		this, &MainWindow::ToggleMenuButton);
	connect(ui->upper_view->power_button, &QPushButton::released,
		this, &MainWindow::TogglePowerButton);

	// set device list to combo box
	device_list = { "Automation", "G1B", "Reglo ICC" };
	ui->upper_view->combo_box->addItems(device_list);

	// load data to para list
	if (para_list->LoadJsonFile() == PROGRAM_NO_CONFIG) {
		MetMsgSubwindow("config file not found");
		exit(PROGRAM_NO_CONFIG);
	}

	// set menu with para list
	ui->upper_view->menu = new MetMenu(para_list, this);
}

MainWindow::~MainWindow()
{
    delete ui;
	delete para_list;
}

void MainWindow::ToggleExitButton()
{
	MetButton* button = ui->upper_view->exit_button;
	button->SetButtonDefault();
	exit(PROGRAM_OK);
}

void MainWindow::ToggleWindowButton()
{
	MetButton* button = ui->upper_view->window_button;
	if (button->status) {
		button->SetButtonDefault();
		showFullScreen();
	} else {
		button->SetButtonPressed();
		showMaximized();
	}
}

void MainWindow::ToggleLoadConfigButton()
{
	MetButton* button = ui->upper_view->load_config_button;
	button->SetButtonDefault();
	if (para_list->LoadJsonFile() == PROGRAM_NO_CONFIG) {
		MetMsgSubwindow("config file not found");
	}
	ui->upper_view->menu->UpdateAttributes();
}

void MainWindow::ToggleMenuButton()
{
	MetButton* button = ui->upper_view->menu_button;
	if (button->status) {
		button->SetButtonDefault();
		ui->upper_view->menu->Close();
	} else {
		button->SetButtonPressed();
		ui->upper_view->menu->Show();
	}
}

void MainWindow::TogglePowerButton()
{
	MetButton* button = ui->upper_view->power_button;
	int current_device = ui->upper_view->combo_box->currentIndex();

	if (button->status) {
		button->SetButtonDefault();
		// remove pages from tab widget
		ui->bottom_view->tab->hide();
		ui->bottom_view->tab->clear();
		ui->upper_view->combo_box->setEnabled(true);
		if (current_device == Device::G1B) {
			ui->bottom_view->g1b_view->~G1BView();
			ui->bottom_view->tab->removeTab(0);
		} else if ((current_device == Device::REGLO_ICC)) {
			ui->bottom_view->reglo_icc_view->~RegloIccView();
			ui->bottom_view->tab->removeTab(0);
		}
	} else {
		button->SetButtonPressed();
		// add pages to tab widget
		int w = 1230;
		int h = 540;
		if (current_device == Device::AUTOMATION) {
			// automation
			QWidget* tab = new QWidget();
			tab->setFixedWidth(w);
			tab->setFixedHeight(h);
			ui->bottom_view->tab->addTab(tab, device_list[Device::AUTOMATION]);
			ui->bottom_view->tab->show();

			// g1b
			ui->bottom_view->g1b_view = new G1BView(w, h, para_list, ui->bottom_view);
			ui->bottom_view->tab->addTab(ui->bottom_view->g1b_view,
				device_list[Device::G1B]);
			if (ui->bottom_view->g1b_view->serial_status == SERIAL_OK)
				ui->bottom_view->tab->show();

			// reglo icc
			ui->bottom_view->reglo_icc_view = new RegloIccView(w, h, para_list, ui->bottom_view);
			ui->bottom_view->tab->addTab(ui->bottom_view->reglo_icc_view,
				device_list[Device::REGLO_ICC]);
			if (ui->bottom_view->reglo_icc_view->serial_status == SERIAL_OK)
				ui->bottom_view->tab->show();
		} else if (current_device == Device::G1B) {
			ui->bottom_view->g1b_view = new G1BView(w, h, para_list, ui->bottom_view);
			ui->bottom_view->tab->addTab(ui->bottom_view->g1b_view,
				device_list[current_device]);
			if (ui->bottom_view->g1b_view->serial_status == SERIAL_OK)
				ui->bottom_view->tab->show();
		} else if (current_device == Device::REGLO_ICC) {
			ui->bottom_view->reglo_icc_view = new RegloIccView(w, h, para_list, ui->bottom_view);
			ui->bottom_view->tab->addTab(ui->bottom_view->reglo_icc_view,
				device_list[current_device]);
			if (ui->bottom_view->reglo_icc_view->serial_status == SERIAL_OK)
				ui->bottom_view->tab->show();
		}
		
		ui->upper_view->combo_box->setEnabled(false);
	}
}