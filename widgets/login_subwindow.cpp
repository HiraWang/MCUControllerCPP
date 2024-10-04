#include "login_subwindow.h"

#include <queue>
#include <thread>
#include <QLabel>
#include <QPixmap>

#include "color.h"
#include "font.h"
#include "../utility.h"
#include "../widgets/button.h"
#include "../widgets/label.h"
#include "../widgets/line_edit.h"
#include "../widgets/loading.h"
#include "../widgets/msg_subwindow.h"

extern std::string IMAGE_MET_ERROR;

MetLoginSubwindow::MetLoginSubwindow(SerialPort* device,
									 QString account,
							         QString password, 
							         QWidget* parent) :
	device(device),
	account(account),
	password(password),
	QDialog(parent)
{
	connect(this, SIGNAL(SignalLoginSubwindowFailed()),
		parent, SLOT(SetSerialStatusFail()));
	connect(this, SIGNAL(SignalLoginSubwindowFinished()),
		parent, SLOT(SetSerialStatusOk()));
	connect(this, SIGNAL(SignalLoginSubwindowFinished()),
		parent, SLOT(SetupUi()));

	LoadStyleSheet();
	SetupUi();
}

MetLoginSubwindow::~MetLoginSubwindow()
{

}

void MetLoginSubwindow::SetupUi()
{
	setFixedWidth(300);
	setFixedHeight(300);
	setStyleSheet(style_sheet);
	setWindowFlag(Qt::FramelessWindowHint);

	MetLabelStyle label_style(FONT_SIZE, FONT_COLOR);
	MetLabel* account_label = new MetLabel(label_style, "Account:", 120, 25, this);
	MetLabel* password_label = new MetLabel(label_style, "Password:", 120, 25, this);

	MetLineEditStyle line_edit_style;
	MetLineEdit* account_edit = new MetLineEdit(line_edit_style, 100, 25, this);
	account_edit->setText(account);
	MetLineEdit* password_edit = new MetLineEdit(line_edit_style, 100, 25, this);
	password_edit->setText(password);

	MetButtonStyle button_style;
	MetButton* login_button = new MetButton(button_style, "LOGIN", "LOGIN", 80, 25, "", "", this);
	connect(login_button, &QPushButton::released, this, &MetLoginSubwindow::Login);

	MetButton* close_button = new MetButton(button_style, "CLOSE", "CLOSE", 80, 25, "", "", this);
	connect(close_button, &QPushButton::released, this, &MetLoginSubwindow::Close);

	QHBoxLayout* account_layout = new QHBoxLayout();
	account_layout->addWidget(account_label, 0, Qt::AlignLeft);
	account_layout->addWidget(account_edit, 0, Qt::AlignRight);

	QHBoxLayout* password_layout = new QHBoxLayout();
	password_layout->addWidget(password_label, 0, Qt::AlignLeft);
	password_layout->addWidget(password_edit, 0, Qt::AlignRight);
	
	layout = new QVBoxLayout(this);
	layout->addStretch(1);
	layout->addItem(account_layout);
	layout->addItem(password_layout);
	layout->addStretch(1);
	layout->addWidget(login_button, 0, Qt::AlignHCenter);
	layout->addWidget(close_button, 0, Qt::AlignHCenter);
	layout->addStretch(1);
	setLayout(layout);

	exec();
}

void MetLoginSubwindow::LoadStyleSheet()
{
	style_sheet =
		"QDialog {"
		"background-color: " + QString(COLOR_GRAY) + ";"
		"border: 2px solid black;"
		"font: bold " + QString(FONT_SIZE) + ";"
		"color: " + QString(COLOR_WHITE) + ";"
		"}";
}

void MetLoginSubwindow::Login()
{
	MetLoadingSubwindow loading;
	// close loading gif
	connect(device, SIGNAL(SignalLoginFailed()), &loading, SLOT(close()));
	connect(device, SIGNAL(SignalLoginFinished()), &loading, SLOT(close()));

	std::thread first(&SerialPort::Login, device);

	loading.exec();
	first.join();

	// close login subwindow
	close();

	extern std::queue<SerialCode> q_login_ret;
	SerialCode ret = q_login_ret.front();

	if (ret == SERIAL_OK) {
		emit SignalLoginSubwindowFinished();
	} else {
		MetMsgSubwindow("login failed");
		emit SignalLoginSubwindowFailed();
	}
}

void MetLoginSubwindow::Close()
{
	close();
	emit SignalLoginSubwindowFailed();
}