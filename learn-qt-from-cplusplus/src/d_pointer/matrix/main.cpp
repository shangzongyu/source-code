#include <iostream>
using namespace std;

class Matrix {
public:
	Matrix() { 
		memset(data, 0, sizeof(data)); 
	}
	Matrix(const Matrix & other ) {
		memcpy(data, other.data, sizeof(data) );
	}
	double & operator()(int row, int col){
		return data[row][col];
	};
	friend ostream & operator<< ( ostream & os, Matrix & m );
private:
	double data[3][3];
};

ostream & operator << ( ostream & os, Matrix & m )
{
	for (int i=0; i<3; i++ ) {
		for (int j=0; j<3; j++)
			os << m.data[i][j] << " ";
	    os << endl;
	}
	return os;
};

int main()
{
	Matrix m1;
	Matrix m2(m1);
	m1(0,0)=10;
	m2(0,0)=20;
	cout << "m1" << endl << m1;
	cout << "m2" << endl << m2;
}
