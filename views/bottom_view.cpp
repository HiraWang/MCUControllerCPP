#include "bottom_view.h"

BottomView::BottomView(QWidget* parent)
    : automation_view(nullptr),
      pulse_gen_view(nullptr),
      pump_view(nullptr),
      monitor_view(nullptr),
      QWidget(parent) {
  SetupUi();
}

BottomView::~BottomView() {}

void BottomView::SetupUi() {
  MetTabStyle tab_style;
  tab = new MetTab(tab_style, this);
  tab->hide();

  layout = new QHBoxLayout(this);
  layout->addWidget(tab, 0, Qt::AlignCenter);
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);
}