#include <string>
#include <iostream>
using namespace std;

struct ci_char_traits: public char_traits <char> {
  static bool eq( char c1, char c2 ){
    return toupper( c1 ) == toupper( c2 );
  } 
  static bool lt( char c1, char c2 ){
    return toupper( c1 ) < toupper( c2 );
  }
  static int compare( const char *s1, const char *s2, size_t n ){
    return memicmp( s1, s2, n );
  }
  static const char *find( const char *s, int n, char a ){
    while ( n-- > 0 && toupper( *s ) != toupper( a ) ){
      ++s;
    }
    return n >= 0 ? s : 0;
  }
};

int main()
{
	typedef basic_string<char, ci_char_traits > ci_string;

	ci_string s1("Apple"), s2("APPLE");
	if ( s1 == s2 ) 
		cout << s1.c_str() <<" equals to " << s2.c_str() << endl;
	else
		cout << s1.c_str() <<" not equals to " << s2.c_str() << endl;

}