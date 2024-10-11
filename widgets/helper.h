#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>

typedef enum {
    PULSE_CHART = 0,
    OSCILLOSCOPE,
    EXAMPLE
} HelperType;

class Helper
{
public:
    Helper(HelperType type);
    void Init(int elapsed);
    void Init(int period, int pulse_width, int voltage, int offset);

public:
    void paint(QPainter* painter, QPaintEvent* event);
    void paint(QPainter* painter, QPaintEvent* event, int elapsed);
    void paint(QPainter* painter, QPaintEvent* event, int period, int pulse_width,
        int voltage, int offset);
    void paint(QPainter* painter, QPaintEvent* event, float scale_x, float scale_y);

private:
    HelperType type;
    QBrush background;
    QBrush circle_brush;
    QBrush line_brush;
    QFont text_font;
    QPen circle_pen;
    QPen line_pen;
    QPen text_pen;
    int elapsed;
    int period;
    int pulse_width;
    int voltage;
    int offset;
};

#endif