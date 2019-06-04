#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QStringList dataList;
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");

    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("stringListModel", QVariant::fromValue(dataList));

    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
