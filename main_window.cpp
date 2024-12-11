#include "main_window.h"

#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>

#include "devices/device.h"
#include "views/automation_view.h"
#include "views/g1b_view.h"
#include "views/monitor_view.h"
#include "views/reglo_icc_view.h"
#include "widgets/msg_subwindow.h"

extern MetMenu* g_menu;
extern std::string IMAGE_MET_CONSOLE;
extern std::string IMAGE_MET_CONFIG;
extern std::string IMAGE_MET_MENU;
extern std::string IMAGE_MET_RESULT;
extern std::string MONITOR_CONFIG_DIR;
extern std::string MONITOR_RESULT_DIR;

MainWindow::MainWindow(QWidget* parent) : 
    QMainWindow(parent), // call superclass constructor with an argument
    ui(new MainWindowUI()),
	para_list(new MetParaList()),
	menu(nullptr)
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
	connect(ui->upper_view->power_button, &QPushButton::released,
		this, &MainWindow::TogglePowerButton);

	// set device and mode list to combo box
	device_list = { "Automation", "G1B", "Reglo ICC", "Monitor" };
	mode_list = { "Normal", "Debug", "UI Test", "Monitor Test" };
	ui->upper_view->device_combo_box->addItems(device_list);
	ui->upper_view->mode_combo_box->addItems(mode_list);

	// load data to para list
	if (para_list->LoadJsonFile() == PROGRAM_NO_CONFIG) {
		MetMsgSubwindow("config file not found");
		exit(PROGRAM_NO_CONFIG);
	}

	// set menu with para list
	ui->upper_view->menu = new MetDialog(para_list, this);
}

MainWindow::~MainWindow()
{
    delete ui;
	delete para_list;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton) {
		if (g_menu)
			g_menu->close();

		menu = new MetMenu();

		QIcon icon_dialog = QIcon(QString::fromStdString(GetAbsPath(IMAGE_MET_MENU)));
		QAction* act_dialog = menu->addAction(icon_dialog, "Show dialog");
		connect(act_dialog, &QAction::triggered, this, [=]()
			{
				ToggleMenuButton();
				menu->close();
				menu = nullptr;
			});

		QIcon icon_console = QIcon(QString::fromStdString(GetAbsPath(IMAGE_MET_CONSOLE)));
		QAction* act_console = menu->addAction(icon_console, "Show console");
		connect(act_console, &QAction::triggered, this, [=]()
			{
				ToggleConsoleButton();
				menu->close();
				menu = nullptr;
			});

		menu->addSeparator();

		QIcon icon_config = QIcon(QString::fromStdString(GetAbsPath(IMAGE_MET_CONFIG)));
		QAction* act_config = menu->addAction(icon_config, "Config directory");
		connect(act_config, &QAction::triggered, this, [=]()
			{
				ToggleConfigDirButton();
				menu->close();
				menu = nullptr;
			});

		QIcon icon_result = QIcon(QString::fromStdString(GetAbsPath(IMAGE_MET_RESULT)));
		QAction* act_result = menu->addAction(icon_result, "Result directory");
		connect(act_result, &QAction::triggered, this, [=]()
			{
				ToggleResultDirButton();
				menu->close();
				menu = nullptr;
			});

		menu->exec(QCursor::pos());
	} else if (event->button() == Qt::LeftButton) {
		if (menu) {
			QAction* action = menu->actionAt(event->pos());
			if (!action) {
				menu->close();
				menu = nullptr;
			}
		}
	}
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

void MainWindow::ToggleConfigDirButton()
{
	std::wstring config_dir = std::wstring(MONITOR_CONFIG_DIR.begin(), MONITOR_CONFIG_DIR.end());
	ShellExecute(nullptr, L"open", nullptr, nullptr, config_dir.c_str(), SW_SHOWNORMAL);
}

void MainWindow::TogglePowerButton()
{
	MetButton* button = ui->upper_view->power_button;

	extern int g_mode;
	int current_device = ui->upper_view->device_combo_box->currentIndex();
	g_mode = ui->upper_view->mode_combo_box->currentIndex();

	if (button->status) {
		button->SetButtonDefault();
		// remove pages from tab widget
		ui->bottom_view->tab->hide();
		ui->bottom_view->tab->clear();
		ui->upper_view->device_combo_box->setEnabled(true);
		ui->upper_view->mode_combo_box->setEnabled(true);

		if (current_device == Device::AUTOMATION) {
			ui->bottom_view->automation_view->~AutomationView();
			ui->bottom_view->monitor_view->~MonitorView();
			ui->bottom_view->g1b_view->~G1BView();
			ui->bottom_view->reglo_icc_view->~RegloIccView();
			for (int i = 0; i < ui->bottom_view->tab->count(); i++) {
				ui->bottom_view->tab->removeTab(i);
			}
			ui->bottom_view->automation_view = nullptr;
			ui->bottom_view->monitor_view = nullptr;
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
		int h = height() - 170;
		if (current_device == Device::AUTOMATION) {
			ui->bottom_view->g1b_view = new G1BView(w, h,
				para_list, ui->bottom_view);
			ui->bottom_view->reglo_icc_view = new RegloIccView(w, h,
				para_list, ui->bottom_view);
			ui->bottom_view->monitor_view = new MonitorView(w, h,
				para_list, ui->bottom_view);
			ui->bottom_view->automation_view = new AutomationView(w, h,
				ui->bottom_view->g1b_view->g1b,
				ui->bottom_view->reglo_icc_view->reglo_icc,
				ui->bottom_view->monitor_view,
				ui->bottom_view);

			ui->bottom_view->tab->addTab(ui->bottom_view->automation_view,
				device_list[Device::AUTOMATION]);
			ui->bottom_view->tab->addTab(ui->bottom_view->monitor_view,
				device_list[Device::MONITOR]);
			ui->bottom_view->tab->addTab(ui->bottom_view->g1b_view,
				device_list[Device::G1B]);
			ui->bottom_view->tab->addTab(ui->bottom_view->reglo_icc_view,
				device_list[Device::REGLO_ICC]);

			if (ui->bottom_view->g1b_view->serial_status == SERIAL_OK &&
				ui->bottom_view->reglo_icc_view->serial_status == SERIAL_OK &&
				ui->bottom_view->monitor_view->serial_status == SERIAL_OK &&
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
		
		ui->upper_view->device_combo_box->setEnabled(false);
		ui->upper_view->mode_combo_box->setEnabled(false);
	}
}

MainWindowController::MainWindowController() :
	window(nullptr)
{
}

MainWindowController::~MainWindowController()
{
	delete window;
}

void MainWindowController::Show() {
	window = new MainWindow;
	window->show();
}