#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QtGui>

class FindDialog : public QDialog {
	Q_OBJECT
public:
	FindDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FindDialog();

private slots:
     void findClicked();
     void enableFindButton(const QString &text);

private:
     QLabel *label;
     QLineEdit *lineEdit;
     QCheckBox *caseCheckBox;
     QCheckBox *backwardCheckBox;
     QPushButton *findButton;
     QPushButton *closeButton; 
};


#endif // FINDDIALOG_H
