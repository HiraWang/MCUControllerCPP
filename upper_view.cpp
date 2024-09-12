#include "upper_view.h"

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

	layout = new QHBoxLayout();
	layout->addWidget(button);
	this->setLayout(layout);

	// Connect button signal to appropriate slot
	//connect(m_button, &QPushButton::released, this, &MainWindow::handleButton);
}