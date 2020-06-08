#include "myview.h"
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QDebug>

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    // 分别获取鼠标点击处在视图、场景和图形项中的坐标，并输出
    QPoint viewPos = event->pos();
    qDebug() << "viewPos: " << viewPos;
    QPointF scenePos = mapToScene(viewPos);
    qDebug() << "scenePos: " << scenePos;
    QGraphicsItem *item = scene()->itemAt(scenePos, QTransform());
    if (item) {
        QPointF itemPos = item->mapFromScene(scenePos);
        qDebug() << "itemPos: " << itemPos;
    }
}

