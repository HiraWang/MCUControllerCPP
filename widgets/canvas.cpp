#include "canvas.h"

#include <QTimer>

extern std::string MONITOR_RESULT_DIR;

MetCanvas::MetCanvas(Helper* helper, int w, int h, QWidget* parent)
    : QWidget(parent), helper(helper), call_render(false) {
  setFixedSize(w, h);
  setAutoFillBackground(false);
}

MetCanvas::~MetCanvas() {}

void MetCanvas::animate() { update(); }

void MetCanvas::paintEvent(QPaintEvent* event) {
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);
  helper->paint(&painter, event);
  if (call_render) {
    QPixmap pixmap(this->size());
    this->render(&pixmap);
    pixmap.save(QString::fromStdString(MONITOR_RESULT_DIR) + "\\canvas.png");
    call_render = false;
  }
  painter.end();
}

void MetCanvas::SetRenderFlag(bool status) { this->call_render = status; }

MetGlCanvas::MetGlCanvas(Helper* helper, QWidget* parent)
    : helper(helper), QOpenGLWidget(parent) {
  setFixedSize(200, 200);
  setAutoFillBackground(false);
}

MetGlCanvas::~MetGlCanvas() {}

void MetGlCanvas::animate() { update(); }

void MetGlCanvas::paintEvent(QPaintEvent* event) {
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);
  helper->paint(&painter, event);
  painter.end();
}