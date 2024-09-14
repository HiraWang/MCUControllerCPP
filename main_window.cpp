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
		if (button->icon_path_default.isEmpty()) {
			button->setText(button->name_default);
		} else if (button->icon_path_default !=
				   button->icon_path_pressed) {
			button->setIcon(button->icon_default);
		}
		button->setStyleSheet(button->style_sheet_default);
		button->status = false; // default
		showFullScreen();
	} else {
		if (button->icon_path_pressed.isEmpty()) {
			button->setText(button->name_pressed);
		} else if (button->icon_path_default !=
				   button->icon_path_pressed) {
			button->setIcon(button->icon_pressed);
		}
		button->setStyleSheet(button->style_sheet_pressed);
		button->status = true; // pressed
		showMaximized();
	}
}

void MainWindow::toggle_power_button()
{
	METButton* button = ui->upper_view->power_button;
	if (button->status) {
		if (button->icon_path_default.isEmpty()) {
			button->setText(button->name_default);
		} else if (button->icon_path_default !=
				   button->icon_path_pressed) {
			button->setIcon(button->icon_default);
		}
		button->setStyleSheet(button->style_sheet_default);
		button->status = false; // default
	} else {
		if (button->icon_path_pressed.isEmpty()) {
			button->setText(button->name_pressed);
		} else if (button->icon_path_default !=
				   button->icon_path_pressed) {
			button->setIcon(button->icon_pressed);
		}
		button->setStyleSheet(button->style_sheet_pressed);
		button->status = true; // pressed
	}
}