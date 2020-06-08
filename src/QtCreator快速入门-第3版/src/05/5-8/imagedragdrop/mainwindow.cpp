#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QPainter>
#include <QMimeData>
#include <QDrag>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);                      // 设置窗口部件可以接收拖入
    QLabel *label = new QLabel(this);          // 创建标签
    QPixmap pix("../imagedragdrop/logo.png");
    label->setPixmap(pix);                     // 添加图片
    label->resize(pix.size());                 // 设置标签大小为图片的大小
    label->move(100,100);
    label->setAttribute(Qt::WA_DeleteOnClose); // 当窗口关闭时销毁图片

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)   //鼠标按下事件
{
    // 第一步：获取图片
    // 将鼠标指针所在位置的部件强制转换为QLabel类型
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if(!child->inherits("QLabel")) return; // 如果部件不是QLabel则直接返回
    QPixmap pixmap = *child->pixmap();     // 获取QLabel中的图片

    // 第二步：自定义MIME类型
    QByteArray itemData;                                     // 创建字节数组
    QDataStream dataStream(&itemData, QIODevice::WriteOnly); // 创建数据流
    // 将图片信息，位置信息输入到字节数组中
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    // 第三步：将数据放入QMimeData中
    QMimeData *mimeData = new QMimeData;  // 创建QMimeData用来存放要移动的数据
    // 将字节数组放入QMimeData中，这里的MIME类型是我们自己定义的
    mimeData->setData("myimage/png", itemData);

    // 第四步：将QMimeData数据放入QDrag中
    QDrag *drag = new QDrag(this);      // 创建QDrag，它用来移动数据
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);//在移动过程中显示图片，若不设置则默认显示一个小矩形
    drag->setHotSpot(event->pos() - child->pos()); // 拖动时鼠标指针的位置不变

    // 第五步：给原图片添加阴影
    QPixmap tempPixmap = pixmap; // 使原图片添加阴影
    QPainter painter;            // 创建QPainter，用来绘制QPixmap
    painter.begin(&tempPixmap);
    // 在图片的外接矩形中添加一层透明的淡黑色形成阴影效果
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    child->setPixmap(tempPixmap); // 在移动图片过程中，让原图片添加一层黑色阴影

    // 第六步：执行拖放操作
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction)
            == Qt::MoveAction)  // 设置拖放可以是移动和复制操作，默认是复制操作
        child->close();         // 如果是移动操作，那么拖放完成后关闭原标签
    else {
        child->show();            // 如果是复制操作，那么拖放完成后显示标签
        child->setPixmap(pixmap); // 显示原图片，不再使用阴影
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) // 拖动进入事件
{
      // 如果有我们定义的MIME类型数据，则进行移动操作
     if (event->mimeData()->hasFormat("myimage/png")) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
     } else {
         event->ignore();
     }
}
void MainWindow::dragMoveEvent(QDragMoveEvent *event)   // 拖动事件
{
     if (event->mimeData()->hasFormat("myimage/png")) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
     } else {
         event->ignore();
     }
}

void MainWindow::dropEvent(QDropEvent *event) // 放下事件
{
    if (event->mimeData()->hasFormat("myimage/png")) {
         QByteArray itemData = event->mimeData()->data("myimage/png");
         QDataStream dataStream(&itemData, QIODevice::ReadOnly);
         QPixmap pixmap;
         QPoint offset;
         // 使用数据流将字节数组中的数据读入到QPixmap和QPoint变量中
         dataStream >> pixmap >> offset;
         // 新建标签，为其添加图片，并根据图片大小设置标签的大小
         QLabel *newLabel = new QLabel(this);
         newLabel->setPixmap(pixmap);
         newLabel->resize(pixmap.size());
   // 让图片移动到放下的位置，不设置的话，图片会默认显示在(0,0)点即窗口左上角
         newLabel->move(event->pos() - offset);
         newLabel->show();
         newLabel->setAttribute(Qt::WA_DeleteOnClose);
         event->setDropAction(Qt::MoveAction);
         event->accept();
     } else {
         event->ignore();
     }
}

