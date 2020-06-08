#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QMediaPlayer;
class QVideoWidget;

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

    QMediaPlayer *player;
    QVideoWidget *videoWidget;

};

#endif // WIDGET_H
