#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent *event);

};

#endif // MYVIEW_H
