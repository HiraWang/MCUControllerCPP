#include "painter.h"

#include <QtOpenGLWidgets/QOpenGLWidget>

class MetCanvas : public QOpenGLWidget
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
    int elapsed;
};