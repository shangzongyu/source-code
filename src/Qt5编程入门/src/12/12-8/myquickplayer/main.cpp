#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QWindow>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    QObject* root = engine.rootObjects().value(0);
    if (QWindow *window = qobject_cast<QWindow *>(root))
        window->show();

    return app.exec();
}
