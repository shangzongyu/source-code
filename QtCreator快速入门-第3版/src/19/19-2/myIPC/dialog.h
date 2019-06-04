#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSharedMemory>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QSharedMemory sharedMemory;

public slots:
    void loadFromFile();
    void loadFromMemory();

private slots:
    void on_loadFromFileButton_clicked();

    void on_loadFromSharedMemoryButton_clicked();

private:
    void detach();

};

#endif // DIALOG_H
