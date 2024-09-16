#include <QStyleOption>
#include <QPainter>

#include "main_window.h"

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
	} else {
		button->set_button_pressed();
	}
}