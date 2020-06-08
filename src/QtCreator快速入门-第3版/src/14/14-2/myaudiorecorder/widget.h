#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QAudioRecorder;

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

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void updateProgress(qint64 duration);

private:
    Ui::Widget *ui;

    QAudioRecorder *audioRecorder;
};

#endif // WIDGET_H
