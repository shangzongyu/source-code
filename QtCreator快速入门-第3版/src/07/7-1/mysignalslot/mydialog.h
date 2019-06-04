#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();

private:
    Ui::MyDialog *ui;


signals:
    void dlgReturn(int);                  // 自定义的信号

private slots:
    void on_pushButton_clicked();
};

#endif // MYDIALOG_H
