#include <iostream>
using namespace std;

class Matrix;
class MatrixData {
	int refCount;
	double data[3][3];
	friend Matrix;
	friend ostream & operator<< ( ostream & os, Matrix & m );
public:
	MatrixData(){
		memset(data, 0, sizeof(data));
	}
};

class Matrix {
public:
	Matrix() { 
		d = new MatrixData;
		d->refCount = 1;
	}
	Matrix(const Matrix & other ) {
		d = other.d;
		d->refCount++;
	}
	~Matrix() {
		if ( --d->refCount == 0 )
            delete d;
	}
	double & operator()(int row, int col){
		detach();
		return d->data[row][col];
	};
	void detach(){
		if ( d->refCount <= 1 ) return;
		d->refCount--;
		d = new MatrixData( *d );
		d->refCount = 1;
	}
	friend ostream & operator<< ( ostream & os, Matrix & m );
private:
	MatrixData * d;
};


ostream & operator << ( ostream & os, Matrix & m )
{
	for (int i=0; i<3; i++ ) {
		for (int j=0; j<3; j++)
			os << m.d->data[i][j] << " ";
	    os << endl;
	}
	os << "refCount=" << m.d->refCount << " " << endl;
	return os;
};

int main()
{
	Matrix m1;
	Matrix m2(m1),m3(m1);
	m3(0,0)=10;
	cout << "m1" << endl << m1;
	cout << "m2" << endl << m2;
	cout << "m3" << endl << m3;
}
