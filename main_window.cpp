#include <QStyleOption>
#include <QPainter>

#include "main_window.h"
#include "views/g1b_view.h"
#include "devices/device.h"

MainWindow::MainWindow(QWidget* parent) : 
    QMainWindow(parent), // call superclass constructor with an argument
    ui(new MainWindowUI()),
	para_list(new METParaList())
{
	// set main window ui
    ui->setup_ui(this);

	// connet widgets with main window callback functions 
	connect(ui->upper_view->exit_button, &QPushButton::released,
		this, &MainWindow::toggle_exit_button);
	connect(ui->upper_view->window_button, &QPushButton::released,
		this, &MainWindow::toggle_window_button);
	connect(ui->upper_view->load_config_button, &QPushButton::released,
		this, &MainWindow::toggle_load_config_button);
	connect(ui->upper_view->menu_button, &QPushButton::released,
		this, &MainWindow::toggle_menu_button);
	connect(ui->upper_view->power_button, &QPushButton::released,
		this, &MainWindow::toggle_power_button);

	// set device list to combo box
	device_list = { "Automation", "G1B", "Reglo ICC" };
	ui->upper_view->combo_box->addItems(device_list);

	// set menu with para list
	ui->upper_view->menu = new METMenu(para_list, this);
}

MainWindow::~MainWindow()
{
    delete ui;
	delete para_list;
}

void MainWindow::toggle_exit_button()
{
	METButton* button = ui->upper_view->exit_button;
	button->set_button_default();
	exit(0);
}

void MainWindow::toggle_window_button()
{
	METButton* button = ui->upper_view->window_button;
	if (button->status) {
		button->set_button_default();
		showFullScreen();
	} else {
		button->set_button_pressed();
		showMaximized();
	}
}

void MainWindow::toggle_load_config_button()
{
	METButton* button = ui->upper_view->load_config_button;
	button->set_button_default();
	para_list->load_json_file();
	ui->upper_view->menu->update_attributes();
}

void MainWindow::toggle_menu_button()
{
	METButton* button = ui->upper_view->menu_button;
	if (button->status) {
		button->set_button_default();
		ui->upper_view->menu->close();
	} else {
		button->set_button_pressed();
		ui->upper_view->menu->show();
	}
}

void MainWindow::toggle_power_button()
{
	METButton* button = ui->upper_view->power_button;
	int current_device = ui->upper_view->combo_box->currentIndex();

	if (button->status) {
		button->set_button_default();
		// remove pages from tab widget
		ui->bottom_view->tab->hide();
		ui->bottom_view->tab->clear();
		ui->upper_view->combo_box->setEnabled(true);
		if (current_device == Device::G1B) {
			ui->bottom_view->g1b_view->~G1BView();
		}
	} else {
		button->set_button_pressed();
		// add pages to tab widget
		int w = 1230;
		int h = 540;
		if (current_device == Device::AUTOMATION) {
			for (const auto& device : device_list)
			{
				QWidget* tab = new QWidget();
				tab->setFixedWidth(w);
				tab->setFixedHeight(h);
				ui->bottom_view->tab->addTab(tab, device);
				ui->bottom_view->tab->show();
			}
		} else if (current_device == Device::G1B) {
			ui->bottom_view->g1b_view = new G1BView(w, h, para_list, ui->bottom_view);
			ui->bottom_view->tab->addTab(ui->bottom_view->g1b_view, device_list[current_device]);
			ui->bottom_view->tab->show();
		} else if (current_device == Device::REGLO_ICC) {
			QWidget* tab = new QWidget();
			tab->setFixedWidth(w);
			tab->setFixedHeight(h);
			ui->bottom_view->tab->addTab(tab, device_list[current_device]);
			ui->bottom_view->tab->show();
		}
		
		ui->upper_view->combo_box->setEnabled(false);
	}
}