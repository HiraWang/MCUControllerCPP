#ifndef PAINTER_H
#define PAINTER_H

#include <QBrush>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>

class Helper
{
public:
    Helper();

public:
    void paint(QPainter* painter, QPaintEvent* event, int elapsed);

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
};

#endif