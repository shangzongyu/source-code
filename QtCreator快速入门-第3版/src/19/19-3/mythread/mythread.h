#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void stop();
protected:
    void run();
private:
    volatile bool stopped;
};


#endif // MYTHREAD_H
