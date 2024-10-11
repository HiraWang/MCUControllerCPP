#ifndef CANVAS_H
#define CANVAS_H

#include "helper.h"

#include <QtOpenGLWidgets/QOpenGLWidget>

class MetCanvas : public QWidget
{
    Q_OBJECT

public:
    MetCanvas(Helper* helper, QWidget* parent);
    virtual ~MetCanvas();

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Helper* helper;
};

class MetGlCanvas : public QOpenGLWidget
{
    Q_OBJECT

public:
    MetGlCanvas(Helper* helper, QWidget* parent);
    virtual ~MetGlCanvas();

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Helper* helper;
};

#endif