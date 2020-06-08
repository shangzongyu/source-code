#include "myitem.h"
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

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
    if (hasFocus()) {
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
    if (event->key() == Qt::Key_Down)
        moveBy(0, 10);
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
