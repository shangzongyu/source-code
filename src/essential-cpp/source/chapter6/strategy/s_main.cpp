/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;

// ******************************
// do i need to store the vector
// or can i access it through the ns element????
// ********************************

// various test programs
extern void prog1();
extern void prog2();
extern void prog3();

int main()
{
	// prog1();
	// prog2();
	prog3();

	return 0; // quiets vc++
}

typedef unsigned int uint;

template <typename seq_type>
class num_sequence;

template <typename seq_type>
ostream& operator<<( ostream &os, const num_sequence<seq_type> &ns );

template <typename seq_type>
class num_sequence {
public:
    typedef vector<unsigned int>::iterator iterator;

	num_sequence( int len=1, int bp=1 );
			 
	uint elem( int pos ) const;
	bool is_elem(  unsigned int ) const;
	int  pos_elem( unsigned int ) const;

    const char* what_am_i() const { return seq_type::what_am_i(); }
	static int  max_elems(){ return _max_elems; }
	ostream& print( ostream &os = cout ) const; 

	void set_position( int pos );
	void set_length( int pos );

	bool operator ==( const num_sequence& ) const;
    bool operator !=( const num_sequence& ) const;
	
    const vector<unsigned int>* sequence() const
		{ return _pelems; }

	iterator begin() const 
		 { return _pelems->begin()+_beg_pos-1; }

	iterator end() const 
		 { return _pelems->begin()+_beg_pos+_length; }

	int length()  const { return _length;  }
    int beg_pos() const { return _beg_pos; }

protected:
	void gen_elems( int pos ) const { _ns.gen_elems( pos ); }
	bool check_integrity( int pos, int size ) const;
	int _calc_pos( unsigned int elem ) const;

	seq_type		   _ns;
	int                _length; 	
    int                _beg_pos;  
	vector<uint>      *_pelems;
	static const int   _max_elems;
};

template <typename seq_type>
const int num_sequence<seq_type>::_max_elems = 1024;

template <typename seq_type>
ostream& 
operator<<( ostream &os, const num_sequence<seq_type> &ns )
{  
    return ns.print( os );
}

template <typename seq_type>
inline bool 
num_sequence<seq_type>::
operator==( const num_sequence &rhs ) const 
{
	return ( _beg_pos == rhs._beg_pos ) &&
		   ( _length  == rhs._length );
}

template <typename seq_type>
inline bool 
num_sequence<seq_type>::
operator !=( const num_sequence &rhs ) const 
	{ return ! ( *this == rhs ); }

template <typename seq_type>
inline void 
num_sequence<seq_type>::
set_position( int pos )
{
	if ( pos <= 0 || pos > _max_elems ){
		 cerr << "!! invalid position: " << pos 
			  << " setting pos to default value of 1\n"
			  << "If inadequate, invoke set_position(pos)\n";
		 pos = 1;
	}
	_beg_pos = pos;
}

template <typename seq_type>
inline void 
num_sequence<seq_type>::
set_length( int len )
{
	if ( len <= 0 || len + _beg_pos - 1 > _max_elems ){
		 cerr << "!! invalid length for this object: " << len 
			  << " setting length to default value of 1\n"
			  << "If inadequate, invoke set_length(len)\n";
	     len = 1;
	}
	_length = len;
}

template <typename seq_type>
num_sequence<seq_type>::
num_sequence( int beg_pos, int len )
	: _pelems( seq_type::elemset() )
{ 
	set_position( beg_pos ); 
	set_length( len ); 
}

template <typename seq_type>
uint num_sequence<seq_type>::
elem( int pos ) const 
{
	return ( ! check_integrity( pos, _pelems->size() ))
		     ? 0 : (*_pelems)[ pos-1 ];
}

template <typename seq_type>
bool num_sequence<seq_type>::
check_integrity( int pos, int size ) const
{
	if ( pos <= 0 || pos > max_elems() )
	{
		 cerr << "!! invalid position: " << pos
			  << " Cannot honor request\n";
		 return false;
	}

	if ( pos > size )
		 gen_elems( pos );

	return true;
}

template <typename seq_type>
ostream& num_sequence<seq_type>::
print( ostream &os ) const
{
		
	int elem_pos = _beg_pos-1;
	int end_pos = elem_pos + _length;

    if ( ! check_integrity( end_pos, _pelems->size() ))
			 return os;

     os << "( "
	    << _beg_pos << " , "
	    << _length << " ) ";
   
	while ( elem_pos < end_pos )
		     os << (*_pelems)[ elem_pos++ ] << ' ';

	return os;
}

// is_elem() returns true if the element passed in a valid element 
// in the object's sequence. For example, if the object represents 
// a fibonacci sequence { 1,1, 2, 3, 5, 8, 13, 21, 34, 45}, beginning 
// as position 3 for a length of 2, then
//    Obj.is_elem( 1 ); // false
//    Obj.is_elem( 3 ); // true
//    Obj.is_elem( 5 ); // false
//    Obj.is_elem( 4 ); // false

template <typename seq_type>
inline bool 
num_sequence<seq_type>::
is_elem( unsigned int elem ) const
{
	return ( ! check_integrity( _beg_pos, _length ))
		     ? false : binary_search( begin(), end(), elem );
}

// pos_elem() returns the position of an element within the sequence 
// independent of what the object's position and length. The object 
// simply is used to identify the sequence for which to return a position. 
// If the element value is invalid, return 0. For example, if the object 
// represents a fibonacci sequence, then
//     Obj.pos_elem( 1 ); // returns 1 - ignore duplicate
//     Obj.pos_elem( 32 ); // returns 9
//     Obj.pos_elem( very-large-instance ); // your choice
//     Obj.pos_elem( 4 ); // return 0

template <typename seq_type>
int num_sequence<seq_type>::
pos_elem( unsigned int elem ) const
{
	cout << "pos_elem( " << elem << " )\n";

	if ((*_pelems)[ _pelems->size()-1 ] < elem )
		 return _calc_pos( elem );

	iterator iter = find( _pelems->begin(), _pelems->end(), elem );
	return ( iter == _pelems->end() )
		     ? 0 
			 : distance( _pelems->begin(), iter )+1;
}

template <typename seq_type>
int num_sequence<seq_type>::
_calc_pos( unsigned int elem ) const
{
    // presumption is that check_integrity() has passed
	int pos = _pelems->size()-1;

    cout << "calc_pos invoked()!: elem: " << elem 
		 << " pos: " << pos 
		 << " at: "  << (*_pelems)[ pos ] 
		 << "\n";

	while (( pos < _max_elems ) && 
		   ( (*_pelems)[ pos ] < elem ))
	{
		   _ns.gen_elems( ++pos ); 
		   cout << " pos: " << pos 
		        << " at: "  << (*_pelems)[ pos ] << endl;
	}

	return (( pos < _max_elems ) && 
		   ((*_pelems)[pos] == elem )) ? pos+1 : 0;
}

class Fibonacci {
public:
   void  gen_elems( int pos ) const;
   static vector<uint>* elemset() { return &_elems; }
   static const char* what_am_i() { return "Fibonacci"; }

protected:
   static vector<uint> _elems;
};

class Pell {
public:
public:
   void  gen_elems( int pos ) const;
   static vector<uint>* elemset() { return &_elems; }
   static const char* what_am_i() { return "Pell"; }

protected:
   static vector<uint> _elems;
};

class Lucas {
public:
   void  gen_elems( int pos ) const;
   static vector<uint>* elemset() { return &_elems; }
   static const char* what_am_i() { return "Lucas"; }

protected:
   static vector<uint> _elems;
};

class Triangular {
public:
   void  gen_elems( int pos ) const;
   static vector<uint>* elemset() { return &_elems; }
   static const char* what_am_i() { return "Triangular"; }

protected:
   static vector<uint> _elems;
};

class Square {
public:
   void  gen_elems( int pos ) const;
   static vector<uint>* elemset() { return &_elems; }
   static const char* what_am_i() { return "Square"; }

protected:
   static vector<uint> _elems;
};

class Pentagonal {
public:
   void  gen_elems( int pos ) const;
   static vector<uint>* elemset() { return &_elems; }
   static const char* what_am_i() { return "Pentagonal"; }

protected:
   static vector<uint> _elems;
};

vector<uint> Fibonacci::_elems;
vector<uint> Pell::_elems;
vector<uint> Lucas::_elems;
vector<uint> Triangular::_elems;
vector<uint> Square::_elems;
vector<uint> Pentagonal::_elems;

template <typename seq_type>
inline void 
display( ostream &os, const num_sequence<seq_type> &ns, int pos )
{
	os << "The element at position " 
	   << pos            << " for the "
	   << ns.what_am_i() << " sequence is " 
	   << ns.elem( pos ) << endl;
}

template <typename seq_type>
inline void 
display( ostream &os, const num_sequence<seq_type> &ns, 
		 int pos, int elem_val )
{
	os << "The element at position " << pos 
	   << " for the "
	   << ns.what_am_i() 
	   << " sequence is " << elem_val << endl;
}

void prog1()
{
	const int pos = 8;

	num_sequence<Fibonacci> fib;	
	display( cout, fib, pos );

	num_sequence<Pell> pell;
	display( cout, pell, pos );

	num_sequence<Lucas> lucas;
	display( cout, lucas, pos );

	num_sequence<Triangular> trian;
	display( cout, trian, pos );
	
	num_sequence<Square> square;
	display( cout, square, pos );

	num_sequence<Pentagonal> penta;
    display( cout, penta, pos );
}

void prog2()
{
	num_sequence<Fibonacci>  fib( 1, 8 );
	cout << "fib: " << fib.what_am_i() << endl;
	num_sequence<Pell>       pell( 4, 6 );
	num_sequence<Lucas>      lucas( 7, 10 );
	num_sequence<Triangular> trian( 1, 12 );
	num_sequence<Square>     square( 6, 6 );
	num_sequence<Pentagonal> penta( 1, 8 );
	
	cout << "fib: "    << fib    << '\n'
	     << "pell: "   << pell   << '\n'
		 << "lucas: "  << lucas  << '\n'
		 << "trian: "  << trian  << '\n'
		 << "square: " << square << '\n'
		 << "penta: "  << penta  << endl;
};

template <typename seq_type>
void prog_3( seq_type ns, int elem_values )
{
	int elem_val = 0;
	const int pos = 8;
	const int find_pos = 14;

    elem_val = ns.elem( pos );
    display( cout, ns, pos, elem_val );
	cout << ns.what_am_i() << " : ( " 
		 << ns.beg_pos()   << ", "
		 << ns.length()    << " ) : "
		 << ns;
	cout << endl;

	ns.set_length( 12 );
	cout << ns << endl;

	cout << "num_sequence::is_elem() ";
	if ( ! ns.is_elem( elem_val ) ||
		   ns.is_elem( 2*elem_val ))
				 cout << "failed\n";
	else cout << "ok!\n";

	cout << "copy constructor and equality ";
	seq_type ns2 = ns;
	if ( ns != ns2 )
		 cout << "failed!\n";
	else cout << "ok!\n";

	ns2.set_position( 5 );
 
	int posit = ns.pos_elem( elem_val );
	if ( ns.pos_elem( elem_val ) != pos )
	     cout << "pos_elem() failed : " << posit << "\n";
	else cout << "pos_elem() -- ok: " << posit << "\n";

	posit = ns.pos_elem( elem_values );
    if ( posit != find_pos ) 
		 cout << "pos_elem(): not found but grown: failed: " 
			  << posit << " correct: " << find_pos << "\n";
    else cout << "pos_elem(): not found but grown: ok\n";

	cout << "about to print final ns vector: \n";
	ns.print();
	cout << endl;
		  
	cout << "ns2: should begin at position 5:\n" 
		 << ns2 << endl;
}

void prog3()
{
	int elem_values[] = 
		{ 377, 80782, 843, 105, 196, 287 };
	
	// for ( int ix = 0; ix < 6; ++ix ) // test all
	for ( int ix = 0; ix < 1; ++ix )    // test 1 at time
	{
		switch( ix ) {
		case 0: {
			num_sequence<Fibonacci> ns( 1,8 );
			prog_3( ns, elem_values[ix] );
			break;}
		case 1:{
			num_sequence<Pell> ns( 1,8 );
			prog_3( ns, elem_values[ix] );
			break;}
		case 2:{
			num_sequence<Lucas> ns( 1,8 );
			prog_3( ns, elem_values[ix] );
			break;}
		case 3:{
			num_sequence<Triangular> ns( 1,8 );
			prog_3( ns, elem_values[ix] );
			break;}
		case 4:{
			num_sequence<Square> ns( 1,8 );
			prog_3( ns, elem_values[ix] );
			break;}
		case 5:{
			num_sequence<Pentagonal> ns( 1,8 );
			prog_3( ns, elem_values[ix] );
			break;}
		default:
			return;
		}	
	}
}
	
void Fibonacci::
gen_elems( int pos ) const
{   
	if ( pos <= 0 || 
		 pos > num_sequence<Fibonacci>::max_elems() )
		       return;

    if ( _elems.empty() )
       { _elems.push_back( 1 ); _elems.push_back( 1 ); }

    if ( _elems.size() <= pos )
	{
		    int ix = _elems.size();
			int n_2 = _elems[ ix-2 ], 
				n_1 = _elems[ ix-1 ];

			int elem;
			for ( ; ix <= pos; ++ix ){
				    elem = n_2 + n_1; 
					// cout << "gen_elems: " << elem << endl;
					_elems.push_back( elem );
					n_2 = n_1; n_1 = elem;
			}
	 }
}
   
void Pell::
gen_elems( int pos ) const    
{    
	if ( pos <= 0 || 
		 pos > num_sequence<Pell>::max_elems() )
		       return;

    if ( _elems.empty() )
       {  _elems.push_back( 1 ); _elems.push_back( 2 ); }

    if ( _elems.size() <= pos )
	{
		    int ix = _elems.size();
			int n_2 = _elems[ ix-2 ], 
				n_1 = _elems[ ix-1 ];

			int elem;
			for ( ; ix <= pos; ++ix ){
				    elem = n_2 + 2 * n_1; 
					_elems.push_back( elem );
					n_2 = n_1; n_1 = elem;
			}
	 }
}
   
void Lucas::
gen_elems( int pos ) const
{     
	if ( pos <= 0 || 
		 pos > num_sequence<Lucas>::max_elems() )
		       return;

    if ( _elems.empty() )
       {  _elems.push_back( 1 ); _elems.push_back( 3 ); }

    if ( _elems.size() <= pos )
	{
		    int ix = _elems.size();
			int n_2 = _elems[ ix-2 ], 
				n_1 = _elems[ ix-1 ];

			int elem;
			for ( ; ix <= pos; ++ix ){
				    elem = n_2 +  n_1; 
					_elems.push_back( elem );
					n_2 = n_1; n_1 = elem;
			}
	 }
}    

void Triangular::
gen_elems( int pos ) const
{
	if ( pos <= 0 || 
		 pos > num_sequence<Triangular>::max_elems() )
		       return;

    if ( _elems.size() <= pos )
	{
		int end_pos = pos+1;
		int ix = _elems.size()+1;
		
		for ( ; ix <= end_pos; ++ix )
			  _elems.push_back( ix*(ix+1)/2 );
	}
}

void Square::
gen_elems( int pos ) const
{
	if ( pos <= 0 || 
		 pos > num_sequence<Square>::max_elems() )
		       return;

    if ( _elems.size() <= pos )
	{
		int end_pos = pos + 1;
		int ix = _elems.size()+1;
		for ( ; ix <= end_pos; ++ix )
			  _elems.push_back( ix*ix );
	}
}   
    
void Pentagonal::
gen_elems( int pos ) const
{
	if ( pos <= 0 || 
		 pos > num_sequence<Pentagonal>::max_elems() )
		       return;

    if ( _elems.size() <= pos )
	{
		int end_pos = pos + 1;
		int ix = _elems.size()+1;
		for ( ; ix <= end_pos; ++ix )
			  _elems.push_back( ix*(3*ix-1)/2 );
	}
}
