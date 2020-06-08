#ifndef HELLODIALOG_H
#define HELLODIALOG_H

#include <QDialog>

namespace Ui {
class HelloDialog;
}

class HelloDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelloDialog(QWidget *parent = 0);
    ~HelloDialog();

private:
    Ui::HelloDialog *ui;
};

#endif // HELLODIALOG_H
