#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QGraphicsView>
#include "myitem.h"

int main(int argc,char* argv[ ])
{
    QApplication app(argc,argv);
    // 新建场景
    QGraphicsScene scene;
    // 创建矩形图形项
    MyItem *item = new MyItem;
    // 将图形项添加到场景中
    scene.addItem(item);
    // 输出(50, 50)点处的图形项
    qDebug() << scene.itemAt(50, 50, QTransform());

    // 为场景创建视图
    QGraphicsView view(&scene);
//    // 设置场景的前景色
//    view.setForegroundBrush(QColor(255, 255, 0, 100));
//    // 设置场景的背景图片
//    view.setBackgroundBrush(QPixmap("../myScene/background.png"));

    scene.setForegroundBrush(QColor(255, 255, 0, 100));
    scene.setBackgroundBrush(QPixmap("../myscene/background.png"));

    view.resize(400, 300);
    view.show();

    QGraphicsView view2(&scene);
    view2.resize(400, 300);
    view2.show();

    return app.exec();
}
