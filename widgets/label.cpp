#include "label.h"

MetLabel::MetLabel(MetLabelStyle style, QString name, int w, int h,
                   QWidget* parent)
    : style(style), w(w), h(h), QLabel(parent) {
  setText(name);
  setFixedSize(QSize(w, h));
  LoadStyleSheet();
  setStyleSheet(style_sheet);
}

MetLabel::~MetLabel() {}

void MetLabel::LoadStyleSheet() {
  style_sheet =
      "QLabel {"
      "background-color: " +
      style.bkg_color +
      ";"
      "font: " +
      style.font_style + " " + style.font_size +
      ";"
      "color: " +
      style.font_color +
      ";"
      "}";
}

MetLabelStyle::MetLabelStyle(QString bkg_color, QString font_size,
                             QString font_color, QString font_style)
    : bkg_color(bkg_color),
      font_size(font_size),
      font_color(font_color),
      font_style(font_style) {}

MetLabelStyle::~MetLabelStyle() {}