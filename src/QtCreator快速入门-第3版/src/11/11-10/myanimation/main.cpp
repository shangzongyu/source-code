#include <QApplication>
#include <QPushButton>
#include <QPropertyAnimation>

int main(int argc, char* argv[ ])
{
    QApplication app(argc, argv);
    QPushButton button("Animated Button");
    button.show();
    QPropertyAnimation animation(&button, "geometry");

    animation.setDuration(2000);
    animation.setStartValue(QRect(250, 0, 120, 30));
    animation.setEndValue(QRect(250, 300, 120, 30));
    animation.setEasingCurve(QEasingCurve::OutBounce);

    animation.start();
    return app.exec();
}
