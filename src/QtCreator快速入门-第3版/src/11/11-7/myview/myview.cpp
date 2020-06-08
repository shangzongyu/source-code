#include "myview.h"
#include <QKeyEvent>

MyView::MyView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void MyView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Plus :
        scale(1.2, 1.2);
        break;
    case Qt::Key_Minus :
        scale(1 / 1.2, 1 / 1.2);
        break;
    case Qt::Key_Right :
        rotate(30);
        break;
    }
    QGraphicsView::keyPressEvent(event);
}
