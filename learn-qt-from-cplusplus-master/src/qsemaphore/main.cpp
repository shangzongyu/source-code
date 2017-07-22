#include <QSemaphore>
#include <QThread>

const int DataSize	 = 500;	
const int BufferSize = 100;
char buffer[BufferSize];
QSemaphore freeElements(BufferSize);
QSemaphore usedElements;

class Producer : public QThread {
public:
	void run(){
		for (int i = 0; i < DataSize; ++i) {
			freeElements.acquire();
			buffer[i % BufferSize] = '0' + i % 10;
			usedElements.release();
		}
	}
};
class Consumer : public QThread {
public:
    void run(){
		for (int i = 0; i < DataSize; ++i) {
			usedElements.acquire();
			fprintf(stdout, "%c", buffer[i % BufferSize]);
			freeElements.release();
		}
	}
};
int main()
{
    Producer producer;
    Consumer consumer;
    producer.start();   consumer.start();
    producer.wait();    consumer.wait();
    return 0;
}
