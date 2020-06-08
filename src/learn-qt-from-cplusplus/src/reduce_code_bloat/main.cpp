#include <iostream>

template <class T>
class Vector {
	T * v;
	int sz;
public:
	Vector(int size=100) {
		v = new T[size]; sz=size;
	};
	~Vector() {
		delete [] v;
	}
	T& operator[](int i) {
		return v[i];
	};
};

typedef Vector<void*> VPVector;

template<class T> 
class Vector <T*>: public VPVector{
public:
	T*& operator[](int i) {
		return (T*&)(VPVector::operator[](i));
	};
};

int main()
{
	Vector<int*>  v1;
	Vector<double*> v2;

	int    i = 3;    v1[0] = &i;
	double d = 3.14; v2[0] = &d;
}