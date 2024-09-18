#include "utility.h"
#include "bottom_view.h"

BottomView::BottomView(QWidget* parent) :
	QWidget(parent)
{
	setup_ui();
}

BottomView::~BottomView()
{
	delete layout;
}

void BottomView::setup_ui()
{
	METTabStyle tab_style;
	tab = new METTab(tab_style, this);
	tab->hide();

	layout = new QHBoxLayout();
	layout->addWidget(tab, 0, Qt::AlignCenter);
	setLayout(layout);
}