#ifndef CANVAS_H
#define CANVAS_H

#include "helper.h"

#include <QtOpenGLWidgets/QOpenGLWidget>

class MetCanvas : public QWidget
{
    Q_OBJECT

public:
    MetCanvas(Helper* helper, int w, int h, QWidget* parent);
    virtual ~MetCanvas();
    void SetRenderFlag(bool status);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    bool call_render;
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