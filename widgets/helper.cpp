#include "helper.h"

#include <iostream>

Helper::Helper(HelperType type) : 
    type(type)
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 32, 64));
    circle_brush = QBrush(gradient);
    circle_pen = QPen(Qt::black);
    circle_pen.setWidth(1);
    line_brush = QBrush(gradient);
    line_pen = QPen(Qt::white);
    line_pen.setWidth(1);
    text_pen = QPen(Qt::white);
    text_font.setPixelSize(12);

    elapsed = 0;
    period = 0;
    pulse_width = 0;
    voltage = 0;
    offset = 0;
}

void Helper::Init(int elapsed) 
{
    this->elapsed = elapsed;
}

void Helper::Init(int period, int pulse_width, int voltage, int offset)
{
    this->period = period;
    this->pulse_width = pulse_width;
    this->voltage = voltage;
    this->offset = offset;
}

void Helper::paint(QPainter* painter, QPaintEvent* event)
{
    if (type == HelperType::PULSE_CHART) {
        paint(painter, event, period, pulse_width, voltage, offset);
    } else if (type == HelperType::EXAMPLE) {
        paint(painter, event, elapsed);
    }
}

void Helper::paint(QPainter* painter, QPaintEvent* event, int elapsed)
{
    painter->fillRect(event->rect(), background);
    painter->translate(100, 100);    
    painter->save();
    painter->setBrush(circle_brush);
    painter->setPen(circle_pen);
    painter->rotate(elapsed * 0.030);

    qreal r = elapsed / 1000.0;
    int n = 30;
    for (int i = 0; i < n; ++i) {
        painter->rotate(30);
        qreal factor = (i + r) / n;
        qreal radius = 0 + 120.0 * factor;
        qreal circleRadius = 1 + factor * 20;
        painter->drawEllipse(QRectF(radius, -circleRadius,
            circleRadius * 2, circleRadius * 2));
    }
    painter->restore();    
    painter->setPen(text_pen);
    painter->setFont(text_font);
    painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));
}

void Helper::paint(QPainter* painter, QPaintEvent* event, int period,
    int pulse_width, int voltage, int offset)
{
    std::list<std::string> info_list = {
        "period : " + std::to_string(period) + " ns",
        "pulse width : " + std::to_string(pulse_width) + " ns",
        "voltage : " + std::to_string(voltage) + " V",
        "offset : " + std::to_string(offset) + " V"
    };

    int info_count = 4;
    int text_box_h = 15;
    int width = event->rect().width();
    int height = event->rect().height();
    int interval = width / 10;
    float duty_cycle = (float)(pulse_width) / (float)(period);
    float period_f = (float)(width);
    float pulse_width_f = (float)(period_f * duty_cycle);
    int voltage_max = (height - 1);
    int voltage_t = (voltage_max - (voltage + offset));

    // draw background
    painter->fillRect(event->rect(), QBrush(QColor(60, 60, 60)));
    painter->translate(0, 0);

    // draw grid
    painter->setPen(QPen(QColor(100, 100, 100)));
    for (int i = 0; i < width; i += interval) {
        painter->drawLine(i, 0, i, height);
    }
    for (int i = 0; i < height; i += interval) {
        painter->drawLine(0, i, width, i);
    }

    // draw data
    painter->setBrush(line_brush);
    painter->setPen(line_pen);
    painter->drawLine(0, voltage_t, (int)pulse_width_f, voltage_t);
    painter->drawLine((int)pulse_width_f, voltage_t, (int)pulse_width_f, voltage_max);
    painter->drawLine((int)pulse_width_f, voltage_max, width, voltage_max);

    // draw text
    painter->setPen(text_pen);
    painter->setFont(text_font);
    for (int i = 0; i < info_count; i++) {
        QString info = QString::fromStdString(info_list.front());
        info_list.pop_front();
        painter->drawText(QRect(5, i * text_box_h + 3, 150, (i + 1) * text_box_h),
            Qt::AlignLeft, info);
    }

    // draw border
    QPen border_pen = QPen(QColor(0, 0, 0));
    border_pen.setWidth(4);
    painter->setPen(border_pen);
    painter->drawLine(0, 0, width, 0);
    painter->drawLine(0, 0, 0, height);
    painter->drawLine(width, 0, width, height);
    painter->drawLine(0, height, width, height);
}
