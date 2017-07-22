/* This file is part of the examples of the Qt Toolkit. */

#ifndef MOUSE_H
#define MOUSE_H

#include <QGraphicsItem>

class Mouse : public QGraphicsItem
{
public:
    Mouse();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int step);

private:
    qreal angle;
    qreal speed;
    qreal mouseEyeDirection;
    QColor color;
};

#endif
