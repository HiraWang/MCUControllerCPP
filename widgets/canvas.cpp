#include "canvas.h"

#include <QTimer>

MetCanvas::MetCanvas(Helper* helper, QWidget* parent) :
    QWidget(parent),
    helper(helper)
{
    elapsed = 0;
    setFixedSize(200, 200);
}

MetCanvas::~MetCanvas()
{

}

void MetCanvas::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}

void MetCanvas::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
    painter.end();
}

MetGlCanvas::MetGlCanvas(Helper* helper, QWidget* parent) : 
    helper(helper),
    QOpenGLWidget(parent)
{
    elapsed = 0;
    setFixedSize(200, 200);
    setAutoFillBackground(false);
}

MetGlCanvas::~MetGlCanvas()
{

}

void MetGlCanvas::animate()
{
    elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}

void MetGlCanvas::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
    painter.end();
}