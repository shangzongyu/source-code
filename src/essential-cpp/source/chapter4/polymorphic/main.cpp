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
#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;

class num_sequence;
ostream operator<<( ostream&, const num_sequence& );

class num_sequence {
public:
	typedef vector<unsigned int>::iterator iterator;
	typedef void (num_sequence::*PtrType)( int );

	enum ns_type { 
		 ns_unset,
		 ns_fibonacci, ns_pell, ns_lucus,
		 ns_triangular, ns_square, ns_pentagonal 
	};

	void set_position( int pos )
	{
		if ( pos <= 0 || pos > max_seq ){
			 cerr << "!! invalid position: " << pos 
				  << " setting pos to default value of 1\n"
				  << "If inadequate, invoke set_position(pos)\n";
			 pos = 1;
		}
		_beg_pos = pos;
	}

	void set_length( int len )
	{
		if ( len <= 0 || len + _beg_pos - 1 > max_seq ){
			 cerr << "!! invalid length for this object: " << len 
				  << " setting length to default value of 1\n"
			      << "If inadequate, invoke set_length(len)\n";
			 len = 1;
		}
		_length = len;
	}

	// Note: do not need a copy constructor, copy assignment operator
	//       or a destructor for the num-sequence class ...

	num_sequence( int beg_pos = 1, int len = 1, ns_type nst = ns_unset )
	{	
	    set_position( beg_pos );
		set_length( len );
	    set_sequence( nst );
	}

	bool operator==( const num_sequence &rhs ) const
	{
		return ( _beg_pos == rhs._beg_pos ) &&
			   ( _length  == rhs._length );
	}

	bool operator !=( const num_sequence &rhs ) const
	{
		return ! ( *this == rhs );
	}

	num_sequence operator+( const num_sequence &rhs )
	{
		return num_sequence( _beg_pos < rhs._beg_pos ? _beg_pos : rhs._beg_pos,
							 _length + rhs._length,
							 _isa == rhs._isa ? _isa : ns_unset );
	}

	bool check_integrity( int pos ) const
	{
	    if (( pos <= 0 ) || ( pos > max_seq ) || ( pos  >= _length + _beg_pos ))
		{
			 cerr << "!! invalid position: " << pos
			      << " Cannot honor request\n";
		     return false;
		}

		if ( _isa == ns_unset ) 
		{
			 cerr << "!! object is not set to a sequence."
				  << " Please set_sequence() and try again!\n";
			 return false;
		}

		if ( pos > _elem->size()){
		     cout << "check_integrity: calculating "
				  << pos - _elem->size() << " additional elements\n";
		     ( this->*_pmf )( pos );
		}

		return true;
	}
			 
	int elem( int pos )
	{
	    if ( ! check_integrity( pos ))
			 return 0;

		return (*_elem)[ pos-1 ];
	}

	// _pmf addresses one of these		 
    void fibonacci( int pos );
    void pell( int pos );      
    void lucus( int pos );     
    void triangular( int pos );
	void square( int pos );    
    void pentagonal( int pos );
 
    void set_sequence( ns_type nst )
	{
		switch ( nst ) {
		  default:
			cerr << "invalid type: setting to 0\n";
			// deliberate fall through

		  case ns_unset:
			_pmf = 0;
			_elem = 0;
			_isa = ns_unset;
			break;
	
		  case ns_fibonacci:  case ns_pell:   case ns_lucus:
		  case ns_triangular: case ns_square: case ns_pentagonal:
			_pmf = func_tbl[ nst ];
			_elem = &seq[ nst ];
			_isa = nst;
			break;
		}
	}

	const char* what_am_i() const
	{
		static char *names[ cnt_seq ] = {
			"not set",
			"fibonacci",
			"pell",
			"lucus",
			"triangular",
			"square",
			"pentagonal"
		};

		return names[ _isa ];
	}

	static void init_seq_map() 
	{
		seq_map[ "fibonacci" ] = ns_fibonacci;
		seq_map[ "pell" ] = ns_pell;   
		seq_map[ "lucus" ] = ns_lucus;
		seq_map[ "triangular" ] = ns_triangular; 
		seq_map[ "square" ] = ns_square; 
		seq_map[ "pentagonal" ] = ns_pentagonal;
	}

	static ns_type seq_type( const char *ps ) 
	{
		if ( seq_map.empty() )
			 init_seq_map();

		string nm( ps );
		return ( seq_map.count( nm ))
			   ? seq_map[ nm ]
			   : ns_unset;
	}

	ostream& print( ostream &os = cout ) const
	{
		if ( ! check_integrity( _length + _beg_pos - 1 ))
			 return os;

		int len = _beg_pos + _length - 1;

		for ( int ix = _beg_pos-1; ix < len; ++ix )
			  os << (*_elem)[ix] << ' ';

		return os;
	}

	ostream& display( ostream &os = cout ) const
	{
		if ( ! check_integrity( 1 ))
			 return os;

		for ( int ix = 0; ix < _elem->size(); ++ix )
			  os << (*_elem)[ix] << ' ';

		return os;
	}

	static ns_type nstype( int num ) 
	{
		return num <= 0 || num > cnt_seq
			   ? ns_unset
			   : static_cast< ns_type >( num );
	}

	static int num_of_sequences() { return cnt_seq; }

	int beg_pos() const { return _beg_pos; }
	int length()  const { return _length;  }

    bool begin( iterator &iter ) const 
	{ 
		if ( ! check_integrity( _length + _beg_pos - 1 )) 
			  return false; 

		iter = _elem->begin()+_beg_pos-1;
		return true; 
	}

	bool end( iterator &iter ) const 
	{ 
		if ( ! check_integrity( _length + _beg_pos - 1 )) 
			  return false;

		iter = _elem->begin() + _beg_pos-1 + _length;  
		return true;
	} 

	const vector<unsigned int>* sequence() const
	{
		if ( ! check_integrity( _length + _beg_pos - 1 )) 
			 return 0;
		return _elem;
	}

	// is_elem() returns true if the element passed in a valid element 
	// in the object's sequence. For example, if the object represents 
	// a fibonacci sequence { 1,1, 2, 3, 5, 8, 13, 21, 34, 45}, beginning 
	// as position 3 for a length of 2, then
    //    Obj.is_elem( 1 ); // false
    //    Obj.is_elem( 3 ); // true
    //    Obj.is_elem( 5 ); // false
    //    Obj.is_elem( 4 ); // false

	bool is_elem( unsigned int elem )
	{
	     if ( ! check_integrity( _length + _beg_pos - 1 ))
			  return false;

         iterator bit, endit;
		 begin( bit ); end( endit );

	     return binary_search( bit, endit, elem );
	}
		

    int pos_elem( unsigned int elem );

private:
	int _calc_pos( unsigned int elem );

    vector<unsigned int> *_elem;
    PtrType				  _pmf;
	ns_type				  _isa;

	int			          _beg_pos;
	int			          _length;
	int                   _max_pos;

	static vector<vector<unsigned int> > seq;

	// static const int            cnt_seq = 7;
	enum { cnt_seq = 7 };

	static const int            max_seq;
	static map<string,ns_type>  seq_map;
	static PtrType              func_tbl[ cnt_seq ];
};

// const int num_sequence::cnt_seq = 7;
const int num_sequence::max_seq = 64;

vector<vector<unsigned int> > num_sequence::seq( cnt_seq );
map<string,num_sequence::ns_type> num_sequence::seq_map;

num_sequence::PtrType 
num_sequence::func_tbl[ cnt_seq ] = {
	0,
	&num_sequence::fibonacci,
    &num_sequence::pell,
	&num_sequence::lucus,
	&num_sequence::triangular,
	&num_sequence::square,
	&num_sequence::pentagonal
};

inline void display( ostream &os, const num_sequence &ns, 
					 int pos, int elem_val )
{
	os << "The element at position " << pos 
	   << " for the "
	   << ns.what_am_i() 
	   << " sequence is " << elem_val << endl;
}

int main()
{
	num_sequence ns( 1, 8);
	int elem_val = 0;
	const int pos = 8;
	const int find_pos = 14;

	int elem_values[] = { 0, 377, 80782, 843, 105, 196, 287 }; 
	// for ( int ix = 1; ix < num_sequence::num_of_sequences(); ++ix )
	for ( int ix = 4; ix < 5; ++ix )
	{
	      ns.set_sequence( num_sequence::nstype( ix ));
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
		  num_sequence ns2 = ns;
		  if ( ns != ns2 )
			   cout << "failed!\n";
		  else cout << "ok!\n";

		  ns2.set_position( 5 );

		  num_sequence ns3 = ns + ns2;
		  if ( ns3.length() != ns.length() + ns2.length() )
			   cout << "operator+ failed in length()\n";
		  else cout << "operator+ succeeded in length()\n";

		  // vc++-ism for min() ,,,
		  if ( ns3.beg_pos() != _MIN( ns.beg_pos(), ns2.beg_pos() ))
			   cout << "operator+ failed in beg_pos()\n";
		  else cout << "operator+ succeeded in beg_pos()\n";
		  
		  int posit = ns.pos_elem( elem_val );
		  if ( ns.pos_elem( elem_val ) != pos )
	           cout << "pos_elem() failed : " << posit << "\n";
		  else cout << "pos_elem() -- ok: " << posit << "\n";

		  posit = ns.pos_elem( elem_values[ix] );
          if ( posit != find_pos ) 
			   cout << "pos_elem(): not found but grown: failed: " << posit << " correct: " << find_pos << "\n";
		  else cout << "pos_elem(): not found but grown: ok\n";

		  cout << "about to display final ns vector: \n";
		  ns.display();
		  cout << endl;
		  
		  cout << "ns2: should begin at position 5:\n" << ns2 << endl;

	}

	return 0; // to quiet VC++
}

ostream operator<<( ostream &os, const num_sequence &ns )
{
    ns.print( os );
	return os;
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

int num_sequence::
pos_elem( unsigned int elem )
{
	cout << "pos_elem( " << elem << " )\n";

	if ( ! check_integrity( 1 ))
		 return 0;

	vector< unsigned int > &this_seq = seq[ _isa ];
	iterator iter;

	if ( (*_elem)[ _elem->size()-1 ] < elem )
		 return _calc_pos( elem );

	if (( iter = find( _elem->begin(), _elem->end(), elem ))
		               == _elem->end() )
		 return 0;
    else return distance( _elem->begin(), iter )+1;
}

int num_sequence::
_calc_pos( unsigned int elem )
{
    // presumption is that check_integrity() has passed
	int pos = _elem->size()-1;

    cout << "calc_pos invoked()!: elem: " << elem 
		 << " pos: " << pos 
		 << " at: "  << (*_elem)[ pos ] 
		 << "\n";

	while (( pos < max_seq ) && ( (*_elem)[ pos ] < elem ))
	{
		   ( this->*_pmf )( ++pos );
		   cout << " pos: " << pos 
		        << " at: "  << (*_elem)[ pos ] << endl;

	}

	return (( pos < max_seq ) && 
		   ((*_elem)[pos] == elem )) ? pos+1 : 0;
}

void num_sequence::
fibonacci( int pos ) 
{   
	if ( pos <= 0 || pos > max_seq )
		 return;

    if ( _elem->empty() )
       {  _elem->push_back( 1 ); _elem->push_back( 1 ); }

    if ( _elem->size() <= pos )
	{
		    int ix = _elem->size();
			int n_2 = (*_elem)[ ix-2 ], 
				n_1 = (*_elem)[ ix-1 ];

			int elem;
			for ( ; ix <= pos; ++ix ){
				    elem = n_2 + n_1; 
					_elem->push_back( elem );
					n_2 = n_1; n_1 = elem;
			}
	 }
}
   
void num_sequence::pell( int pos )     
{    
	if ( pos <= 0 || pos > max_seq )
		 return;

    if ( _elem->empty() )
       {  _elem->push_back( 1 ); _elem->push_back( 2 ); }

    if ( _elem->size() <= pos )
	{
		    int ix = _elem->size();
			int n_2 = (*_elem)[ ix-2 ], 
				n_1 = (*_elem)[ ix-1 ];

			int elem;
			for ( ; ix <= pos; ++ix ){
				    elem = n_2 + 2 * n_1; 
					_elem->push_back( elem );
					n_2 = n_1; n_1 = elem;
			}
	 }
}
   
void num_sequence::lucus( int pos ) 
{     
	if ( pos <= 0 || pos > max_seq )
		 return;

    if ( _elem->empty() )
       {  _elem->push_back( 1 ); _elem->push_back( 3 ); }

    if ( _elem->size() <= pos )
	{
		    int ix = _elem->size();
			int n_2 = (*_elem)[ ix-2 ], 
				n_1 = (*_elem)[ ix-1 ];

			int elem;
			for ( ; ix <= pos; ++ix ){
				    elem = n_2 +  n_1; 
					_elem->push_back( elem );
					n_2 = n_1; n_1 = elem;
			}
	 }
}    
   
void num_sequence::triangular( int pos )
{
	if ( pos <= 0 || pos > max_seq )
		 return;

    if ( _elem->size() <= pos )
	{
		int end_pos = pos+1;
		int ix = _elem->size()+1;
		cout << "tri: ix: " << ix << " pos: " << pos << endl;
		for ( ; ix <= end_pos; ++ix )
			  _elem->push_back( ix*(ix+1)/2 );
	}
}

void num_sequence::square( int pos )
{
 	if ( pos <= 0 || pos > max_seq )
		 return;

    if ( _elem->size() <= pos )
	{
		int end_pos = pos + 1;
		int ix = _elem->size()+1;
		for ( ; ix <= end_pos; ++ix )
			  _elem->push_back( ix*ix );
	}
}   
    
void num_sequence::pentagonal( int pos )
{
 	if ( pos <= 0 || pos > max_seq )
		 return;

    if ( _elem->size() <= pos )
	{
		int end_pos = pos + 1;
		int ix = _elem->size()+1;
		for ( ; ix <= end_pos; ++ix )
			  _elem->push_back( ix*(3*ix-1)/2 );
	}
}