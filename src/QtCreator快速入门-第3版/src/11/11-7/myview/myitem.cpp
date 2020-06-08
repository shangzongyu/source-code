#include "myitem.h"
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QGraphicsEffect>

MyItem::MyItem()
{
    brushColor = Qt::red;

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

}

QRectF MyItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                   QWidget *)
{
    if(hasFocus() || !collidingItems().isEmpty()) {
        painter->setPen(QPen(QColor(255, 255, 255, 200)));
    } else {
        painter->setPen(QPen(QColor(100, 100, 100, 100)));
    }
    painter->setBrush(brushColor);
    painter->drawRect(-10, -10, 20, 20);
}

// 鼠标按下事件处理函数，设置被点击的图形项获得焦点，并改变光标外观
void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setFocus();
    setCursor(Qt::ClosedHandCursor);
}
// 键盘按下事件处理函数，判断是否是向下方向键，如果是，则向下移动图形项
void MyItem::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_1 : {
        QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
        blurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
        blurEffect->setBlurRadius(8);
        setGraphicsEffect(blurEffect);
        break;
    }
    case Qt::Key_2 : {
        QGraphicsColorizeEffect *colorizeEffect = new QGraphicsColorizeEffect;
        colorizeEffect->setColor(Qt::white);
        colorizeEffect->setStrength(0.6);
        setGraphicsEffect(colorizeEffect);
        break;
    }
    case Qt::Key_3 : {
        QGraphicsDropShadowEffect *dropShadowEffect = new QGraphicsDropShadowEffect;
        dropShadowEffect->setColor(QColor(63, 63, 63, 100));
        dropShadowEffect->setBlurRadius(2);
        dropShadowEffect->setOffset(10);
        setGraphicsEffect(dropShadowEffect);
        break;
    }
    case Qt::Key_4 : {
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
        opacityEffect->setOpacity(0.4);
        setGraphicsEffect(opacityEffect);
        break;
    }
    case Qt::Key_5 :
        graphicsEffect()->setEnabled(false);
        break;
    }

}
// 悬停事件处理函数，设置光标外观和提示
void MyItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    setCursor(Qt::OpenHandCursor);
    setToolTip("I am item");
}
// 右键菜单事件处理函数，为图形项添加一个右键菜单
void MyItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *moveAction = menu.addAction("move back");
    QAction *selectedAction = menu.exec(event->screenPos());
    if (selectedAction == moveAction) {
        setPos(0, 0);
    }
}

void MyItem::advance(int phase)
{
    // 在第一个阶段不进行处理
    if (!phase)
        return;
    // 图形项向不同方向随机移动
    int value = qrand() % 100;
    if (value < 25) {
        setRotation(45);
        moveBy(qrand() % 10, qrand() % 10);
    } else if (value < 50) {
        setRotation(-45);
        moveBy(- qrand() % 10, - qrand() % 10);
    } else if (value < 75) {
        setRotation(30);
        moveBy(- qrand() % 10, qrand() % 10);
    } else {
        setRotation(-30);
        moveBy(qrand() % 10, - qrand() % 10);
    }
}

QPainterPath MyItem::shape()
{
    QPainterPath path;
    path.addRect(-10, -10, 20, 20);
    return path;
}


