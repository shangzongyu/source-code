#include <iostream>
using namespace std;

class TYPE {
  public:
	TYPE() { data=0; }
	~TYPE() {
		cout << "~TYPE" << endl;
	}
	int data;
};

static TYPE * get_singleton()                    		
{                           		
	static TYPE this_singleton;              		
	return &this_singleton;   		         		
};


class A {
public:
	~A() {		
		cout << "~A" << endl;
		cout << get_singleton()->data << endl;
	}
} a;


int main()
{
	get_singleton();
	return 0;
}
