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
    void SetExampleInfo(int elapsed);
    void SetPulseChartInfo(int period, int pulse_width, int voltage, int offset);
    void SetCount(size_t count);
    void SetScaleX(float scale_x);
    void SetScaleY(float scale_y);
    float GetScaleX();
    float GetScaleY();

public:
    void paint(QPainter* painter, QPaintEvent* event);
    void paint(QPainter* painter, QPaintEvent* event, int elapsed);
    void paint(QPainter* painter, QPaintEvent* event, int period, int pulse_width,
        int voltage, int offset);
    void paint(QPainter* painter, QPaintEvent* event, size_t count);

private:
    HelperType type;
    QBrush background;
    QBrush circle_brush;
    QBrush line_brush;
    QFont text_font;
    QPen circle_pen;
    QPen line_pen;
    QPen text_pen;

    // example
    int elapsed;

    // pulse chart
    int period;
    int pulse_width;
    int voltage;
    int offset;

    // oscilloscope
    size_t count;
    int buffer_size;
    float scale_x;
    float scale_y;
};

#endif