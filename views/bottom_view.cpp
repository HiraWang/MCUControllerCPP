#include "bottom_view.h"

BottomView::BottomView(QWidget* parent) :
	QWidget(parent)
{
	SetupUi();
}

BottomView::~BottomView()
{

}

void BottomView::SetupUi()
{
	MetTabStyle tab_style;
	tab = new MetTab(tab_style, this);
	tab->hide();

	layout = new QHBoxLayout(this);
	layout->addWidget(tab, 0, Qt::AlignCenter);
	setLayout(layout);
}