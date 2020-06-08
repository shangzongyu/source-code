#include <QThread>
#include <windows.h>

class Thread : public QThread
{
protected:
	void run() {
		for (int i=0; i<5; i++) {
			Beep(800,1000); Sleep(1000);
		}
	};

};


int main()
{
	Thread  t;
	t.start();
	Sleep(1000);
	for (int i=0; i<5; i++) {
		Beep(400,1000); Sleep(1000);
	}
}

