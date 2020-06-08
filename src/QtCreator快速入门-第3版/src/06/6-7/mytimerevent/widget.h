#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    int id1, id2, id3;

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void timerUpdate();


};

#endif // WIDGET_H
