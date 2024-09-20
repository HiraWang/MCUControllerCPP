﻿#include <QStyleOption>
#include <QPainter>

#include "main_window.h"
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
	if (button->status) {
		button->set_button_default();
		// remove pages from tab widget
		ui->bottom_view->tab->hide();
		ui->bottom_view->tab->clear();
		ui->upper_view->combo_box->setEnabled(true);
	} else {
		button->set_button_pressed();
		// add pages to tab widget
		int w = 1230;
		int h = 520;
		int current_device = ui->upper_view->combo_box->currentIndex();
		if (current_device == Device::AUTOMATION) {
			for (const auto& device : device_list)
			{
				QWidget* tab = new QWidget();
				tab->setFixedWidth(w);
				tab->setFixedHeight(h);
				ui->bottom_view->tab->addTab(tab, device);
				ui->bottom_view->tab->show();
			}

			std::string str = para_list->list[PUMP_KEYWORD].str;
			std::wstring wstring = std::wstring(str.begin(), str.end());
			LPCWSTR port = wstring.data();
			std::wcout << port << "" << sizeof(port) << '\n';
			std::wcout << L"COM4" << "" << sizeof(L"COM4") << '\n';

			DeviceG1B G1B(port,
						  CBR_9600,
						  8,
						  ONESTOPBIT,
						  NOPARITY);
			const int size = 5;
			char buf_r[size + 1] = { 0 };
			char buf_w[] = "go\r";

			G1B.open();
			G1B.write(buf_w, strlen(buf_w));
			G1B.read(buf_r, size);
			G1B.close();
		} else if (current_device == Device::G1B) {
			QWidget* tab = new QWidget();
			tab->setFixedWidth(w);
			tab->setFixedHeight(h);
			ui->bottom_view->tab->addTab(tab, device_list[current_device]);
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