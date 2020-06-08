/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
#include <cassert>
using namespace std;

template <typename elemType>
class Matrix 
{
    friend Matrix<elemType> 
    operator+( const Matrix<elemType>&, const Matrix<elemType>& );

    friend Matrix< elemType > 
    operator*( const Matrix<elemType>&, const Matrix<elemType>& );

public:
    Matrix( int rows, int columns );
    Matrix( const Matrix& );
    ~Matrix(){ delete [] _matrix; } 
    Matrix& operator=( const Matrix& );

    void operator+=( const Matrix& );
    elemType& operator()( int row, int column ) 
        { return _matrix[ row * cols() + column ]; }

    const elemType& operator()( int row, int column ) const
        { return _matrix[ row * cols() + column ]; }

    int rows() const { return _rows; }
    int cols() const { return _cols; }

    bool same_size( const Matrix &m ) const 
         { return rows() == m.rows() && cols() == m.cols(); }

    bool comfortable( const Matrix &m ) const
         { return ( cols() == m.rows() ); }

    ostream& print( ostream& ) const;

protected:
    int  _rows;
    int  _cols;
    elemType *_matrix;
};

template <typename elemType>
inline ostream& operator<<( ostream& os, const Matrix<elemType> &m )
    { return m.print( os ); }

// end of Matrix.h
template <typename elemType>
Matrix< elemType > 
operator+( const Matrix<elemType> &m1, const Matrix<elemType> &m2 )
{
    assert( m1.same_size( m2 ) != 0 );

    Matrix<elemType> result( m1 );
    result += m2;
    return result;
}

template <typename elemType>
Matrix<elemType> 
operator*( const Matrix<elemType> &m1, const Matrix<elemType> &m2 )
{
    assert( m1.comfortable( m2 ) != 0 );
    Matrix<elemType> result( m1.rows(), m2.cols() );

    for ( int ix = 0; ix < m1.rows(); ix++ ) {
	   for ( int jx = 0; jx < m1.cols(); jx++ ) {
	         result( ix, jx ) = 0;
	         for ( int kx = 0; kx < m1.cols(); kx++ )
		        result( ix, jx ) += m1( ix, kx ) * m2( kx, jx );
	   }
    }
    return result;
}
    
template <typename elemType>
void Matrix<elemType>::operator+=( const Matrix &m )
{
    assert( same_size( m ) != 0 );
    register int matrix_size = cols() * rows();

    for ( int ix = 0; ix < matrix_size; ++ix )
        ( *( _matrix + ix )) += ( *( m._matrix + ix ));
}

template <typename elemType>
ostream& Matrix<elemType>::print( ostream &os ) const
{
    register int col = cols();
    register int matrix_size = col * rows();

    for ( int ix = 0; ix < matrix_size; ++ix )
    {
	  if ( ix % col == 0 ) os << endl; 
	  os << ( *( _matrix + ix )) << ' ';
    }

    os << endl;
    return os;
}

template <typename elemType>
Matrix<elemType>::Matrix( const Matrix & rhs )
{ 
	_rows = rhs._rows; _cols = rhs._cols;
	int mat_size = _rows * _cols;
   _matrix = new elemType[ mat_size ];
	for ( int ix = 0; ix < mat_size; ++ix )
         _matrix[ ix ] = rhs._matrix[ ix ]; 

}

template <typename elemType>
Matrix<elemType>& Matrix<elemType>::
operator=( const Matrix &rhs ) 
{
	if ( this != &rhs )
   {
    	    _rows = rhs._rows; _cols = rhs._cols;
	     int mat_size = _rows * _cols;
	     delete [] _matrix;
	     _matrix = new elemType[ mat_size ];
	     for ( int ix = 0; ix < mat_size; ++ix )
              _matrix[ ix ] = rhs._matrix[ ix ]; 
    }
    return *this;
}

template <typename elemType>
Matrix<elemType>::Matrix( int rows, int columns )
            : _rows( rows ), _cols( columns )
{ 
    int size = _rows * _cols;
    _matrix = new elemType[ size ];
    for ( int ix = 0; ix < size; ++ix )
          _matrix[ ix ] = elemType(); 
}


#include <fstream>
void ex6_2()
{
	ofstream log( "logmatrix.txt" );
	if ( ! log )
		{ cerr << "can't open log file!\n"; return; }

	Matrix<float> identity( 4, 4 );
    log << "identity: " << identity << endl;

	float ar[16]={
		1., 0., 0., 0., 0., 1., 0., 0.,
		0., 0., 1., 0., 0., 0., 0., 1. };

	for ( int i = 0, k = 0; i < 4; ++i )
		for ( int j = 0; j < 4; ++j )
		    identity( i, j ) = ar[ k++ ];

	log << "identity after set: " << identity << endl;

	Matrix<float> m( identity );
	log << "m: memberwise initialized: " << m << endl; 
	
	Matrix<float> m2( 8, 12 );
	log << "m2: 8x12: " <<  m2  << endl;

	m2 = m;
	log << "m2 after memberwise assigned to m: " << m2 << endl;

	float ar2[16]={
		1.3f, 0.4f, 2.6f, 8.2f, 6.2f, 1.7f, 1.3f, 8.3f,
		4.2f, 7.4f, 2.7f, 1.9f, 6.3f, 8.1f, 5.6f, 6.6f };

	Matrix<float> m3( 4, 4 );

	for ( int ix = 0, kx = 0; ix < 4; ++ix )
		for ( int j = 0; j < 4; ++j )
		    m3( ix, j ) = ar2[ kx++ ];

	log << "m3: assigned random values: " << m3 << endl;

	Matrix<float> m4 = m3 * identity;
	log << m4 << endl;

	Matrix<float> m5 = m3 + m4;
	log << m5 << endl;

	m3 += m4;
	log << m3 << endl;
}

#include <vector>
#include <algorithm>
using namespace std;

void test_rotate()
{
	char ch[] = "boohiss!!";
	rotate( ch, ch+3, ch+7 );
	cout << ch << endl;
}

int main()
{ 
	ex6_2();
	test_rotate();
	return 0; // unnecessary but quiets vc++
}