#include <QThread>
#include <windows.h>
#include <QMutex>

QMutex speaker;
class Thread : public QThread
{
protected:
	void run() {
		for (int i=0; i<4; i++) {
			speaker.lock();Beep(800,1000); speaker.unlock();
			Sleep(1000);
		}
	};

};


int main()
{
	Thread  t;
	t.start();
	for (int i=0; i<5; i++) {
		speaker.lock();Beep(400,1000); speaker.unlock();
		Sleep(1000);
	}
}

