#include <QWaitCondition>
#include <QThread>
#include <QMutex>

const int DataSize   = 500;
const int BufferSize = 100;
char buffer[BufferSize];

QWaitCondition bufferNotEmpty;
QWaitCondition bufferNotFull;
QMutex mutex;
int numUsedElements = 0;

class Producer : public QThread {
public:
    void run() {
		for (int i = 0; i < DataSize; ++i) {
			mutex.lock();
			if (numUsedElements == BufferSize)
				bufferNotFull.wait(&mutex);
			mutex.unlock();

			buffer[i % BufferSize] = '0' + i % 10;

			mutex.lock();
			++numUsedElements;
			bufferNotEmpty.wakeAll();
			mutex.unlock();
		}
	}
};

class Consumer : public QThread {
public:
    void run(){
		for (int i = 0; i < DataSize; ++i) {
			mutex.lock();
			if (numUsedElements == 0)
				bufferNotEmpty.wait(&mutex);
			mutex.unlock();

			fprintf(stdout, "%c", buffer[i % BufferSize]);

			mutex.lock();
			--numUsedElements;
			bufferNotFull.wakeAll();
			mutex.unlock();
		}
	}
};

int main( )
{
    Producer producer;
    Consumer consumer;
    producer.start();   consumer.start();
    producer.wait();    consumer.wait();
    return 0;
}
