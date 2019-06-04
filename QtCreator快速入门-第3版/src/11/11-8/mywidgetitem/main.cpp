#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>
#include <QObject>

int main(int argc, char* argv[ ])
{
    QApplication app(argc, argv);
    QGraphicsScene scene;
    // 创建部件，并关联它们的信号和槽
    QTextEdit *edit = new QTextEdit;
    QPushButton *button = new QPushButton("clear");
    QObject::connect(button, SIGNAL(clicked()), edit, SLOT(clear()));
    // 将部件添加到场景中
    QGraphicsWidget *textEdit = scene.addWidget(edit);
    QGraphicsWidget *pushButton = scene.addWidget(button);
    // 将部件添加到布局管理器中
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    layout->addItem(textEdit);
    layout->addItem(pushButton);
    // 创建图形部件，设置其为一个顶层窗口，然后在其上应用布局
    QGraphicsWidget *form = new QGraphicsWidget;
    form->setWindowFlags(Qt::Window);
    form->setWindowTitle("Widget Item");
    form->setLayout(layout);
    // 将图形部件进行扭曲，然后添加到场景中
    form->setTransform(QTransform().shear(2, -0.5), true);
    scene.addItem(form);
    QGraphicsView view(&scene);
    view.show();
    return app.exec();
}
