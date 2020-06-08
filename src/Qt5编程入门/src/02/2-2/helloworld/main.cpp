#include <QtGui/QApplication>
#include <QDialog>
#include <QLabel>
#include <QTextCodec>
int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QDialog w;
    w.resize(400,300);
    QLabel label(&w);
    label.move(120,120);
    label.setText(QObject::tr("Hello World!ÄãºÃQt£¡"));
    w.show();
    return a.exec();
}
