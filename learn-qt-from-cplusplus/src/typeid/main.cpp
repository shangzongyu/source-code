#include <iostream>
#include <typeinfo>
using namespace std;

class B_np {
	int f() {}
};
class D_np: public B_np {
};

class B {
	virtual int f() {return 0;}
};
class D: public B {
};

int main() 
{
	double d;
	B_np * p1 = new D_np;
	cout << typeid(d).name()   << endl;
	cout << typeid(*p1).name() << endl;

	B * p2 = new D;
	cout << typeid(*p2).name() << endl;

	cout << typeid(p2).name() << endl;

	delete p1;
	delete p2;
}

