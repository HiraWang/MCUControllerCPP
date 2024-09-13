#include "upper_view.h"
#include "widgets/style.h"

UpperView::UpperView(QWidget* parent) :
	QWidget(parent)
{
	this->setup_ui();
}

UpperView::~UpperView()
{
	delete button;
	delete layout;
}

void UpperView::setup_ui()
{
	button = new QPushButton("My Button", this);
	button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

	Style power_button_style;
	power_button = new METButton("ON", "OFF", power_button_style, 200, 50);

	layout = new QHBoxLayout();
	layout->addWidget(button);
	layout->addWidget(power_button);
	this->setLayout(layout);

	// Connect button signal to appropriate slot
	//connect(m_button, &QPushButton::released, this, &MainWindow::handleButton);
}