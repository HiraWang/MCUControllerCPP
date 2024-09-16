#include <QStyleOption>
#include <QPainter>

#include "main_window.h"

MainWindow::MainWindow(QWidget* parent) : 
    QMainWindow(parent), // call superclass constructor with an argument
    ui(new MainWindowUI())
{
    ui->setup_ui(this);

	// connet main window widgets with related callback functions
	connect(ui->upper_view->window_button, &QPushButton::released,
		this, &MainWindow::toggle_window_button);
	connect(ui->upper_view->power_button, &QPushButton::released,
		this, &MainWindow::toggle_power_button);
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