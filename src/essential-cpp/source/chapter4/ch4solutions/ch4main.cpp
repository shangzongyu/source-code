/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Stack {
public:    
	bool   push( const string& );
    bool   pop ( string &elem );
	bool   peek( string &elem );

    bool   find(  const string &elem ) const;
	int    count( const string &elem ) const;

	bool   empty() const { return _stack.empty(); }
	bool   full()  const { return _stack.size() == _stack.max_size(); }
	int    size()  const { return _stack.size(); }

private:
	vector<string> _stack;
};

bool
Stack::pop( string &elem ) 
{
    if ( empty() )
         return false;

    elem = _stack.back();
    _stack.pop_back(); 
    
    return true;
}

bool
Stack::peek( string &elem ) 
{
    if ( empty() )
         return false;

    elem = _stack.back();
    return true;
}

bool
Stack::push( const string &elem ) 
{
    if ( full() )
         return false;

    _stack.push_back( elem );
    return true;
}

#include <algorithm>

bool
Stack::find( const string &elem ) const
{
	vector<string>::const_iterator end_it = _stack.end();
	return std::find( _stack.begin(), end_it, elem ) != end_it;
}

int
Stack::count( const string &elem ) const 
{
	return std::count( _stack.begin(), _stack.end(), elem );
}

// Exercise 4.3

#include <string>
#include <map>
#include <iostream>
using namespace std;

class globalWrapper {
public:
    static int tests_passed()     { return _tests_passed; }
    static int tests_run()        { return _tests_run; }
    static int version_number()   { return _version_number; }
    static string version_stamp() { return _version_stamp; }
    static string program_name()  { return _program_name; }

    static void tests_passed( int nval )  { _tests_passed = nval; }
    static void tests_run( int nval )     { _tests_run = nval; }
    static void version_number( int nval ){ _version_number = nval; }

    static void version_stamp( const string& nstamp )
		{ _version_stamp = nstamp; }

    static void program_name( const string& npn )   
		{ _program_name = npn; }

private:
	static string _program_name;
    static string _version_stamp;
    static int    _version_number;
    static int    _tests_run;
    static int    _tests_passed;
};

string globalWrapper::_program_name;
string globalWrapper::_version_stamp;
int globalWrapper::_version_number;
int globalWrapper::_tests_run;
int globalWrapper::_tests_passed;

// =======================================================
// Exercise 4.4
// =======================================================
class UserProfile {
public:    
	enum uLevel { Beginner, Intermediate, Advanced, Guru };

    UserProfile( string login, uLevel = Beginner );
    UserProfile();

    // default memberwise initialization and copy sufficient
    // no explicit copy constructor or copy assignment operator
    // no destructor necessary ...

    bool operator==( const UserProfile& );
    bool operator!=( const UserProfile &rhs );

    // read access functions 
    string login() const { return _login; }
    string user_name() const { return _user_name; }
    int login_count() const { return _times_logged; }
    int guess_count() const { return _guesses; }
    int guess_correct() const { return _correct_guesses; }
    double guess_average() const;
    string level() const;

    // write access functions
    void reset_login( const string &val ){ _login = val; }
    void user_name( const string &val ){ _user_name = val; }

    void reset_level( const string& );
    void reset_level( uLevel newlevel ) { _user_level = newlevel; }

	void reset_login_count( int val ){ _times_logged = val; }
    void reset_guess_count( int val ){ _guesses = val; }
    void reset_guess_correct( int val ){ _correct_guesses = val; }

    void bump_login_count( int cnt=1 ){ _times_logged += cnt; }
    void bump_guess_count( int cnt=1 ){ _guesses += cnt; }
    void bump_guess_correct(int cnt=1){ _correct_guesses += cnt;}

 private:
   
    static string guest_login();

    string _login;
    string _user_name;
    int    _times_logged;
    int    _guesses;
    int    _correct_guesses;  
    uLevel _user_level;

    static map<string,uLevel> _level_map;
    static void init_level_map();
};

inline double UserProfile::guess_average() const
{ 

	return _guesses 
		   ? double( _correct_guesses ) / double( _guesses ) * 100
		   : 0.0; 
}

inline UserProfile::UserProfile( string login, uLevel level )
    : _login( login ), _user_level( level ),
      _times_logged( 1 ), _guesses( 0 ), _correct_guesses( 0 )
{}

#include <cstdlib>
inline UserProfile::UserProfile()
    : _login( "guest" ), _user_level( Beginner ), 
      _times_logged( 1 ), _guesses( 0 ), _correct_guesses( 0 )
{ 
   static int id = 0;
   char buffer[ 16 ];
   
   // Standard C library function in <cstdlib>
   // turns an integer into an ascii representation
   // _itoa( int value, char *buffer, int radix )
   _itoa( id++, buffer, 10 );

   // add a unique id during session to guest login
   _login += buffer;
}
   
/*
 * the hardest part of implementing this operator is trying
 * to understand what it means: _login & _user_name must be same
 * idea is that this would allow multiple UserProfiles,
 * if present, to be merged ... */
inline bool UserProfile::
operator==( const UserProfile &rhs )
{ 
     if ( _login == rhs._login && 
          _user_name == rhs._user_name ) 
          return true; 
	 else return false;
}

// note: this should appear after the definition
//       of the inline equality operator ...
inline bool UserProfile::
operator !=( const UserProfile &rhs )
       { return ! ( *this == rhs ); } 
    
inline string UserProfile::level() const
{
    static string _level_table[] = {
       "Beginner", "Intermediate", "Advanced", "Guru" };
    return _level_table[ _user_level ];
}

ostream& operator<<( ostream &os, const UserProfile &rhs )
{ /* output of the form:
   * stanl Beginner 12 100 10 10%
   **/
   os << rhs.login() << ' '
      << rhs.level() << ' '
      << rhs.login_count() << ' '
      << rhs.guess_count() << ' '
      << rhs.guess_correct() << ' '
      << rhs.guess_average() << endl;
   return os;
}

// this is probably overkill ...
// but it provides an excuse for a demonstration ...
map<string,UserProfile::uLevel> UserProfile::_level_map;

void UserProfile::init_level_map() 
{
    _level_map[ "Beginner" ] = Beginner;
    _level_map[ "Intermediate" ] = Intermediate;
    _level_map[ "Advanced" ] = Advanced;
    _level_map[ "Guru" ] = Guru;
}

inline void UserProfile::reset_level( const string &level )
{
    if ( _level_map.empty() ) 
		 init_level_map();

    map<string,uLevel>::iterator it;
    _user_level = (( it = _level_map.find( level )) 
                       != _level_map.end() )
                ? it->second : Beginner;
}        

istream& operator>>( istream &is, UserProfile &rhs )
{ // yes, this assumes the input is valid ...
    string login, level;
    is >> login >> level;
    
    int lcount, gcount, gcorrect;
    is >> lcount >> gcount >> gcorrect;

    rhs.reset_login( login );
    rhs.reset_level( level );

    rhs.reset_login_count( lcount );
    rhs.reset_guess_count( gcount );
    rhs.reset_guess_correct( gcorrect );

    return is;
}

void ex_4_4()
{
	UserProfile anon;
	cout << anon;

	UserProfile anon_too;
	cout << anon_too;

	UserProfile anna( "AnnaL", UserProfile::Guru );
	cout << anna;

	anna.bump_guess_count( 27 );
	anna.bump_guess_correct( 25 );
	anna.bump_login_count();

	cout << anna;

	cout << "OK: enter user profile data by hand to see if we can read it\n";
	cin >> anon;
	cout << anon;


}

typedef float elemType; 
class Matrix 
{
    friend Matrix operator+( const Matrix&, const Matrix& );
    friend Matrix operator*( const Matrix&, const Matrix& );

public:
    Matrix( elemType=0.,elemType=0.,elemType=0.,elemType=0.,
            elemType=0.,elemType=0.,elemType=0.,elemType=0.,
            elemType=0.,elemType=0.,elemType=0.,elemType=0.,
            elemType=0.,elemType=0.,elemType=0.,elemType=0. );
    Matrix( const elemType* );
    void operator+=( const Matrix& );
    elemType& operator()( int row, int column ) 
        { return _matrix[ row ][ column ]; }

    // makes transition to general matrix simpler
    int rows() const { return 4; }
    int cols() const { return 4; }

    elemType operator()( int row, int column ) const
        { return _matrix[ row ][ column ]; }

    ostream& print( ostream& ) const;

private:
    elemType _matrix[4][4];
};

inline ostream& operator<<( ostream& os, const Matrix &m )
       { return m.print( os ); }

Matrix operator+( const Matrix &m1, const Matrix &m2 ){
    Matrix result( m1 );
    result += m2;
    return result;
}

Matrix operator*( const Matrix &m1, const Matrix &m2 )
{
    Matrix result;
    for ( int ix = 0; ix < m1.rows(); ix++ ) {
	   for ( int jx = 0; jx < m1.cols(); jx++ ) {
	         result( ix, jx ) = 0;
	         for ( int kx = 0; kx < m1.cols(); kx++ )
		        result( ix, jx ) += m1( ix, kx ) * m2( kx, jx );
	   }
    }
    return result;
}

void Matrix::operator+=( const Matrix &m )
{
    for ( int ix = 0; ix < 4; ++ix )
        for ( int jx = 0; jx < 4; ++jx )
            _matrix[ix][jx] += m._matrix[ix][jx];
}

ostream& Matrix::print( ostream &os ) const 
{
    int cnt = 0;
    for ( int ix = 0; ix < 4; ++ix )
        for ( int jx = 0; jx < 4; ++jx, ++cnt )
        {
            if ( cnt &&  !( cnt % 8 )) os << endl; 
            os << _matrix[ix][jx] << ' ';
        }

	os << endl;
    return os;
}

Matrix::    
Matrix( elemType a11, elemType a12, elemType a13, elemType a14,
        elemType a21, elemType a22, elemType a23, elemType a24,
        elemType a31, elemType a32, elemType a33, elemType a34,
        elemType a41, elemType a42, elemType a43, elemType a44 )
{
   _matrix[0][0] = a11; _matrix[0][1] = a12;
   _matrix[0][2] = a13; _matrix[0][3] = a14;
   _matrix[1][0] = a21; _matrix[1][1] = a22;
   _matrix[1][2] = a23; _matrix[1][3] = a24;
   _matrix[2][0] = a31; _matrix[2][1] = a32;
   _matrix[2][2] = a33; _matrix[2][3] = a34;
   _matrix[3][0] = a41; _matrix[3][1] = a42;
   _matrix[3][2] = a43; _matrix[3][3] = a44;
}

Matrix::    
Matrix( const elemType *array )
{
    int array_index = 0;
    for ( int ix = 0; ix < 4; ++ix )
          for ( int jx = 0; jx < 4; ++jx )
                _matrix[ix][jx] = array[array_index++];
    
}

void ex_4_1() 
{

 	Stack st;
    string str;

	cout << "Please enter a series of strings.\n";
    while ( cin >> str && ! st.full() )
            st.push( str );

    if ( st.empty() ) {
         cout << '\n' << "Oops: no strings were read -- bailing out\n ";
         return;
	 }
         
    st.peek( str );
    if ( st.size() == 1 && str.empty() ) {
         cout << '\n' << "Oops: no strings were read -- bailing out\n ";
         return;
	 }

    cout << '\n' << "Read in " << st.size() << " strings!\n"
		   << "The strings, in reverse order: \n";

    while ( st.size() ) 
		 if ( st.pop( str ))
	         cout << str << ' ';
	
	cout << '\n' << "There are now " << st.size() 
		  << " elements in the stack!\n";
}

void ex_4_2() 
{
	Stack st;

	cout << "Please enter a series of strings.\n";

    string str;
    while ( cin >> str && ! st.full() )
            st.push( str );

    cout << '\n'
	     << "Read in " << st.size() << " strings!\n";

	cin.clear();

	cout << "what word to search for? ";
	cin >> str;
    
	bool found = st.find( str );
	int  count = found ? st.count( str ) : 0;

	cout << str << (found ? " is " : " isn\'t " )
		 << "in the stack. ";

	if ( found ) 
		 cout << "It occurs " << count << " times\n";
}

void ex_4_3()
{
	if ( globalWrapper::program_name().empty() )
	{
		 globalWrapper::program_name( "ex_4_3" );
		 globalWrapper::version_number( 1 );
		 globalWrapper::version_stamp( "A1-OK" );
	}

	if ( globalWrapper::program_name() == "ex_4_3" )
		 cout << "Wrapper seems to work ok\n";
	else cout << "Hmm. Wrapper doesn't seem to be correct\n";
}

void ex_4_5()
{
	Matrix m;
    cout << m << endl;

	elemType ar[16]={
		1., 0., 0., 0., 0., 1., 0., 0.,
		0., 0., 1., 0., 0., 0., 0., 1. };

	Matrix identity( ar );
	cout << identity << endl;

	// guarantee default memberwise copy works correctly
	Matrix m2( identity );
	m = identity;

	cout << m2 << endl; cout << m  << endl;

	elemType ar2[16]={
		1.3f, 0.4f, 2.6f, 8.2f, 6.2f, 1.7f, 1.3f, 8.3f,
		4.2f, 7.4f, 2.7f, 1.9f, 6.3f, 8.1f, 5.6f, 6.6f };

	Matrix m3( ar2 );
	cout << m3 << endl;

	Matrix m4 = m3 * identity;
	cout << m4 << endl;

	Matrix m5 = m3 + m4;
	cout << m5 << endl;

	m3 += m4;
	cout << m3 << endl;

}
	    
typedef void (*pf)();

pf tbl[]  = {
	&ex_4_1, &ex_4_2, &ex_4_3, &ex_4_4, &ex_4_5
};

int main() 
{
	// ex_4_1();
	// ex_4_2();
	// ex_4_3();
	// ex_4_4();
	// ex_4_5();

	// const int test_count = 5;
	// for ( int ix = 0; ix < test_count; ++ix )
	//       tbl[ ix ]();

	// tbl[0]();
	// tbl[1]();
	// tbl[2]();
	// tbl[3]();
	tbl[4]();

	return 0; // quiets vc++
}