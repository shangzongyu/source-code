#include <QObject>
#include <iostream>
using namespace std;

class A : public QObject{
     Q_OBJECT
 public:
	 A() { value=0; }
	 void setValue(int newValue) {
		 if (newValue == value) return;
		 value = newValue;
		 emit stateChanged(value);
	 }
 signals:
     void stateChanged(int newValue);
 private:
     int value;
}; 

class B: public QObject
{
    Q_OBJECT
public slots:
	void process(int newValue) {
		cout << "newValue= " << newValue << endl;
	}
};