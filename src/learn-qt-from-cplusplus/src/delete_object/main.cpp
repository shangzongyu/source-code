#include <iostream>
using namespace std;

class A {
public:
	~A() { cout << " ~A  " ; } 
};

class Wrapper {
	A * p;
public:
	Wrapper( A* _p ): p(_p) { };
	~Wrapper() { cout << " ~Wrapper " ; };
	operator A* () { 
		cout << " converting ";	
		return p; 
	}; 
};

int main()
{
	Wrapper w( new A );
	delete w;
}