#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QObject>
#include <QDebug>
#include <QQuickItem>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 使用QQmlComponent进行加载
    //    QQmlEngine engine;
    //    QQmlComponent component(&engine,
    //                   QUrl(QStringLiteral("qrc:///main.qml")));
    //    QObject *object = component.create();
    //    // ... 进行其他操作
    //    delete object;

    QQuickView view;
    view.setSource( QUrl(QStringLiteral("qrc:///main.qml")));
    view.show();
    QQuickItem *object = view.rootObject();
    object->setWidth(500);
    qDebug() << object->width();

    return app.exec();
}


