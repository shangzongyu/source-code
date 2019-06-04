#include "myitem.h"
#include <QPainter>

MyItem::MyItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
}
QRectF MyItem::boundingRect() const
{
    return QRectF(-10 - 0.5, -10 - 0.5, 20 + 1, 20 + 1);
}
void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                   QWidget *)
{
    painter->drawRect(-10, -10, 20, 20);
}

