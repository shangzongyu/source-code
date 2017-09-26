#include <iostream>
using namespace std;

class Pointer {
	int * ip;
public:
	Pointer(int *_ip): ip(_ip) {};
	int & operator * () {
		cout << "non-const ";	
		return *ip;
	}
	const int & operator * () const {
		cout << " const ";
		return *ip;
	}
};

class Out {
	Pointer p;
public:
	Out(int * _ip):p(_ip){};
	void set() { *p=10; } 
	int get() const { return *p; } 
};

int main()
{
	int x = 0;
	Out o( &x );
	
	o.set();
	o.get();
}