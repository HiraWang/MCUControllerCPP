﻿#include <QStyleOption>
#include <QPainter>

#include "main_window.h"
#include "device.h"

MainWindow::MainWindow(QWidget* parent) : 
    QMainWindow(parent), // call superclass constructor with an argument
    ui(new MainWindowUI())
{
	// set main window ui
    ui->setup_ui(this);

	// connet widgets with main window callback functions 
	connect(ui->upper_view->window_button, &QPushButton::released,
		this, &MainWindow::toggle_window_button);
	connect(ui->upper_view->power_button, &QPushButton::released,
		this, &MainWindow::toggle_power_button);

	// set device list to combo box
	device_list = { "Automation", "G1B", "Reglo ICC" };
	ui->upper_view->combo_box->addItems(device_list);
}

MainWindow::~MainWindow()
{
    delete ui;
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
		int w = 1200;
		int h = 500;
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