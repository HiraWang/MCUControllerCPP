#include "main_window.h"

#include <QPainter>
#include <QStyleOption>

#include "devices/device.h"
#include "views/automation_view.h"
#include "views/g1b_view.h"
#include "views/monitor_view.h"
#include "views/reglo_icc_view.h"
#include "widgets/msg_subwindow.h"

extern std::string MONITOR_RESULT_DIR;

MainWindow::MainWindow(QWidget* parent) : 
    QMainWindow(parent), // call superclass constructor with an argument
    ui(new MainWindowUI()),
	para_list(new MetParaList())
{
	// optimize console
	ResizeConsole(1520, 680);
	DWORD prev_mode;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(handle, &prev_mode);
	SetConsoleMode(handle, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

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
	connect(ui->upper_view->console_button, &QPushButton::released,
		this, &MainWindow::ToggleConsoleButton);
	connect(ui->upper_view->result_dir_button, &QPushButton::released,
		this, &MainWindow::ToggleResultDirButton);
	connect(ui->upper_view->ui_test_button, &QPushButton::released,
		this, &MainWindow::ToggleUiTestButton);
	connect(ui->upper_view->power_button, &QPushButton::released,
		this, &MainWindow::TogglePowerButton);

	// set device list to combo box
	device_list = { "Automation", "G1B", "Reglo ICC", "Monitor" };
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
	HideConsole();
	exit(PROGRAM_OK);
}

void MainWindow::ToggleWindowButton()
{
	MetButton* button = ui->upper_view->window_button;
	if (button->status) {
		button->SetButtonDefault();
		showFullScreen();
		if (ui->bottom_view->automation_view)
			ui->bottom_view->automation_view->ScaleUpSize();
		if (ui->bottom_view->monitor_view)
			ui->bottom_view->monitor_view->ScaleUpCanvasSize();
	} else {
		button->SetButtonPressed();
		showMaximized();
		if (ui->bottom_view->automation_view)
			ui->bottom_view->automation_view->ScaleDownSize();
		if (ui->bottom_view->monitor_view)
			ui->bottom_view->monitor_view->ScaleDownCanvasSize();
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

void MainWindow::ToggleConsoleButton()
{
	MetButton* button = ui->upper_view->console_button;
	//g_out << IsConsoleVisible() << '\n';
	if (button->status) {
		button->SetButtonDefault();
		HideConsole();
	} else {
		button->SetButtonPressed();
		ShowConsole();
	}
}

void MainWindow::ToggleResultDirButton()
{
	MetButton* button = ui->upper_view->result_dir_button;
	button->SetButtonDefault();
	std::wstring result_dir = std::wstring(MONITOR_RESULT_DIR.begin(), MONITOR_RESULT_DIR.end());
	ShellExecute(nullptr, L"open", nullptr, nullptr, result_dir.c_str(), SW_SHOWNORMAL);
}

void MainWindow::ToggleUiTestButton()
{
	MetButton* button = ui->upper_view->ui_test_button;
	extern bool g_normal;
	extern bool g_ui_test;
	if (button->status) {
		button->SetButtonDefault();
		g_ui_test = false;
	} else {
		button->SetButtonPressed();
		g_ui_test = true;
	}
	g_normal = !g_ui_test;
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
		if (current_device == Device::AUTOMATION) {
			ui->bottom_view->automation_view->~AutomationView();
			ui->bottom_view->g1b_view->~G1BView();
			ui->bottom_view->reglo_icc_view->~RegloIccView();
			for (int i = 0; i < ui->bottom_view->tab->count(); i++) {
				ui->bottom_view->tab->removeTab(i);
			}
			ui->bottom_view->automation_view = nullptr;
			ui->bottom_view->g1b_view = nullptr;
			ui->bottom_view->reglo_icc_view = nullptr;
		} else if (current_device == Device::G1B) {
			ui->bottom_view->g1b_view->~G1BView();
			ui->bottom_view->tab->removeTab(0);
			ui->bottom_view->g1b_view = nullptr;
		} else if ((current_device == Device::REGLO_ICC)) {
			ui->bottom_view->reglo_icc_view->~RegloIccView();
			ui->bottom_view->tab->removeTab(0);
			ui->bottom_view->reglo_icc_view = nullptr;
		} else if ((current_device == Device::MONITOR)) {
			ui->bottom_view->monitor_view->~MonitorView();
			ui->bottom_view->tab->removeTab(0);
			ui->bottom_view->monitor_view = nullptr;
		}
	} else {
		button->SetButtonPressed();
		// add pages to tab widget
		int w = width() - 25;
		int h = 550;
		if (current_device == Device::AUTOMATION) {
			ui->bottom_view->g1b_view = new G1BView(w, h,
				para_list, ui->bottom_view);
			ui->bottom_view->reglo_icc_view = new RegloIccView(w, h,
				para_list, ui->bottom_view);
			ui->bottom_view->automation_view = new AutomationView(w, h,
				ui->bottom_view->g1b_view->g1b, ui->bottom_view->reglo_icc_view->reglo_icc, ui->bottom_view);

			ui->bottom_view->tab->addTab(ui->bottom_view->automation_view,
				device_list[Device::AUTOMATION]);
			ui->bottom_view->tab->addTab(ui->bottom_view->g1b_view,
				device_list[Device::G1B]);
			ui->bottom_view->tab->addTab(ui->bottom_view->reglo_icc_view,
				device_list[Device::REGLO_ICC]);

			if (ui->bottom_view->g1b_view->serial_status == SERIAL_OK &&
				ui->bottom_view->reglo_icc_view->serial_status == SERIAL_OK &&
				ui->bottom_view->automation_view->serial_status == SERIAL_OK) {
				ui->bottom_view->tab->show();
			}
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
		} else if (current_device == Device::MONITOR) {
			ui->bottom_view->monitor_view = new MonitorView(w, h, para_list, ui->bottom_view);
			ui->bottom_view->tab->addTab(ui->bottom_view->monitor_view,
				device_list[current_device]);
			if (ui->bottom_view->monitor_view->serial_status == SERIAL_OK)
				ui->bottom_view->tab->show();
		}
		
		ui->upper_view->combo_box->setEnabled(false);
	}
}