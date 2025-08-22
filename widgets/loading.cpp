#include "loading.h"

#include <QLabel>
#include <QMovie>

#include "color.h"
#include "font.h"
#include "utility.h"

extern std::string IMAGE_MET_LOADING;

MetLoadingSubwindow::MetLoadingSubwindow(QWidget* parent) : QDialog(parent) {
  LoadStyleSheet();
  SetupUi();
}

MetLoadingSubwindow::~MetLoadingSubwindow() {}

void MetLoadingSubwindow::SetupUi() {
  setFixedWidth(300);
  setFixedHeight(300);
  setStyleSheet(style_sheet);
  setWindowFlag(Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);

  QMovie* movie =
      new QMovie(QString::fromStdString(GetAbsPath(IMAGE_MET_LOADING)),
                 QByteArray(), this);
  movie->setScaledSize(QSize(100, 100));

  QLabel* label = new QLabel(this);
  label->setAlignment(Qt::AlignCenter);
  label->setMovie(movie);

  movie->start();

  QVBoxLayout* layout_v = new QVBoxLayout();
  layout_v->addWidget(label, 0, Qt::AlignCenter);

  QWidget* container = new QWidget(this);
  container->setLayout(layout_v);

  layout = new QVBoxLayout(this);
  layout->addWidget(container, 0, Qt::AlignCenter);
  setLayout(layout);
}

void MetLoadingSubwindow::LoadStyleSheet() {
  style_sheet =
      "QDialog {"
      "background-color: " +
      QString(COLOR_GRAY) +
      ";"
      "border: 2px solid black;"
      "font: bold " +
      QString(FONT_SIZE) +
      ";"
      "color: " +
      QString(COLOR_WHITE) +
      ";"
      "}";
}