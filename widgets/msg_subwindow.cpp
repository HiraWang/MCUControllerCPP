#include "msg_subwindow.h"

#include <QLabel>
#include <QPixmap>

#include "color.h"
#include "font.h"
#include "../utility.h"
#include "../widgets/buttons.h"

extern std::string IMAGE_MET_ERROR;

METMsgSubwindow::METMsgSubwindow(QString message,
								 QWidget* parent) :
	message(message),
	QDialog(parent)
{
	std::cout << message.toStdString() << '\n';
	load_style_sheet();
	setup_ui();
}

METMsgSubwindow::~METMsgSubwindow()
{

}

void METMsgSubwindow::setup_ui()
{
	setFixedWidth(300);
	setFixedHeight(300);
	setStyleSheet(style_sheet_dialog);
	setWindowFlag(Qt::FramelessWindowHint);

	QPixmap pixmap = QPixmap(QString::fromStdString(get_abs_path(IMAGE_MET_ERROR)));

	QLabel icon;
	icon.setScaledContents(true);
	icon.setPixmap(pixmap.scaled(70, 70, Qt::KeepAspectRatio));

	QLabel label;
	label.setText(message);
	label.setStyleSheet(style_sheet_label);

	METButtonStyle button_style;
	METButton button = METButton(button_style, "OK", "OK", 80, 80, "", "", this);
	connect(&button, &QPushButton::released, this, &QDialog::close);

	layout = new QVBoxLayout(this);
	layout->addWidget(&icon, 0, Qt::AlignHCenter | Qt::AlignBottom);
	layout->addWidget(&label, 0, Qt::AlignHCenter | Qt::AlignVCenter);
	layout->addWidget(&button, 0, Qt::AlignHCenter | Qt::AlignTop);
	setLayout(layout);

	exec();
}

void METMsgSubwindow::load_style_sheet()
{
	style_sheet_dialog =
		"QDialog {"
		"background-color: " + QString(COLOR_GRAY) + ";"
		"border: 2px solid black;"
		"font: bold " + QString(FONT_SIZE) + ";"
		"color: " + QString(COLOR_WHITE) + ";"
		"}";
	style_sheet_label =
		"QLabel {"
		"font: " + QString(FONT_SIZE) + ";"
		"}";
}

