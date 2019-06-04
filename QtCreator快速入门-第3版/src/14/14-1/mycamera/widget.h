#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
};

#endif // WIDGET_H
