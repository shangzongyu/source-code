#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "myitem.h"
#include <QPropertyAnimation>

int main(int argc, char* argv[ ])
{
    QApplication app(argc, argv);
    QGraphicsScene scene;
    scene.setSceneRect(-200, -150, 400, 300);
    MyItem *item = new MyItem;
    scene.addItem(item);
    QGraphicsView view;
    view.setScene(&scene);
    view.show();
    // 为图形项的rotation属性创建动画
    QPropertyAnimation *animation = new QPropertyAnimation(item, "rotation");
    animation->setDuration(2000);
    animation->setStartValue(0);
    animation->setEndValue(360);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    return app.exec();
}
