#ifndef NEWS_DIALOG_H
#define NEWS_DIALOG_H

#include <QtGui>

class NewsDialog : public QDialog
{
    Q_OBJECT

public:
    NewsDialog();

public slots:
    void changeNews(QListWidgetItem *current, QListWidgetItem *previous);

private:
    QListWidget * listWidget;
	QLabel * image; 
	QLabel * news ; 
};

#endif
