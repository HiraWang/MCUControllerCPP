#include "canvas.h"

#include <QTimer>

MetCanvas::MetCanvas(Helper* helper, int w, int h, QWidget* parent) :
    QWidget(parent),
    helper(helper)
{
    setFixedSize(w, h);
    setAutoFillBackground(false);
}

MetCanvas::~MetCanvas()
{

}

void MetCanvas::animate()
{
    update();
}

void MetCanvas::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event);
    painter.end();
}

MetGlCanvas::MetGlCanvas(Helper* helper, QWidget* parent) : 
    helper(helper),
    QOpenGLWidget(parent)
{
    setFixedSize(200, 200);
    setAutoFillBackground(false);
}

MetGlCanvas::~MetGlCanvas()
{

}

void MetGlCanvas::animate()
{
    update();
}

void MetGlCanvas::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event);
    painter.end();
}