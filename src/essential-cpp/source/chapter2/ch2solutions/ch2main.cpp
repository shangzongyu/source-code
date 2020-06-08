/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

extern bool fibon_elem( int, int& );
extern bool calc_elements( vector<int> &vec, int pos );
extern void really_calc_elems( vector<int> &vec, int pos );
extern bool pentagonal_elem( int po, int &elem );
extern const vector<int>*  pentagonal_series( int pos );
extern void display_elems( vector<int>&, 
						   const string&, ostream& = cout );

inline bool check_validity( int pos ) 
{
	return ( pos <= 0 || pos > 64 )
          ? false : true;
}

inline bool calc_elems( vector<int> &vec, int pos )
{
   if ( pos <= 0 || pos > 64 )
   {
        cerr << "Sorry. Invalid position: " << pos << endl;
        return false;
   }
 
   if ( vec.size() < pos )
        really_calc_elems( vec, pos );

   return true;
}

/*
inline int max( int t1, int t2 )
       { return t1 > t2 ? t1 : t2; }

inline float max( float t1, float t2 )
       { return t1 > t2 ? t1 : t2; }

inline string max( const string& t1, const string& t2 )
       { return t1 > t2 ? t1 : t2; }

inline int max( const vector<int> &vec )
       { return *max_element( vec.begin(), vec.end() ); }

inline float max( const vector<float> &vec )
       { return *max_element( vec.begin(), vec.end() ); }

inline string max( const vector<string> &vec )
       { return *max_element( vec.begin(), vec.end() ); }

inline int max( const int *parray, int size )
       { return *max_element( parray, parray+size ); }

inline float max( const float *parray, int size )
       { return *max_element( parray, parray+size ); }

inline string max( const string *parray, int size )
       { return *max_element( parray, parray+size ); }
*/

template <typename Type>
inline Type max( Type t1, Type t2 )
       { return t1 > t2 ? t1 : t2; }

template <typename elemType>
inline elemType max( const vector<elemType> &vec )
       { return *max_element( vec.begin(), vec.end() ); }

template <typename arrayType>
inline arrayType max( const arrayType *parray, int size )
       { return *max_element( parray, parray+size ); }


void ex2_1()
{
   int pos, elem;
   char ch;
   bool more = true;

   while ( more )
   {
       cout << "Please enter a position: ";
       cin >> pos;
    
  	    if ( fibon_elem( pos, elem ))
            cout << "element # " << pos 
                 << " is " << elem << endl;
	    else 
            cout << "Sorry. Could not calculate element # "
                 << pos << endl;

       cout << "would you like to try again? (y/n) ";
       cin >> ch;
       if ( ch != 'y' || ch != 'Y' )
		    more = false;
    }
}

void ex2_2()
{
    vector<int> pent;
    const string title( "Pentagonal Numeric Series" );

    if ( calc_elements( pent, 0 ))
         display_elems( pent, title );

    if ( calc_elements( pent, 8 ))
         display_elems( pent, title );

    if ( calc_elements( pent, 14 ))
         display_elems( pent, title );

	if ( calc_elements( pent, 138 ))
         display_elems( pent, title );
}


void ex2_3() 
{
    vector<int> pent;
    const string title( "Pentagonal Numeric Series" );

    if ( calc_elems( pent, 0 ))
         display_elems( pent, title );

    if ( calc_elems( pent, 8 ))
         display_elems( pent, title );

    if ( calc_elems( pent, 14 ))
         display_elems( pent, title );

	if ( calc_elems( pent, 138 ))
         display_elems( pent, title );
}

void ex2_4() 
{
    int elem;

    if ( pentagonal_elem( 8, elem ))
	      cout << "element 8 is " << elem << '\n';
  
    if ( pentagonal_elem( 88, elem ))
	      cout << "element 88 is " << elem << '\n';

    if ( pentagonal_elem( 12, elem ))
	      cout << "element 12 is " << elem << '\n';

    if ( pentagonal_elem( 64, elem ))
 	      cout << "element 64 is " << elem << '\n';

}

void ex2_5() 
{
    string sarray[]={ "we", "were", "her", "pride", "of", "ten" };
    vector<string> svec( sarray, sarray+6 );

    int iarray[]={ 12, 70, 2, 169, 1, 5, 29 };
    vector<int> ivec( iarray, iarray+7 );

    float farray[]={ 2.5, 24.8, 18.7, 4.1, 23.9 };
    vector<float> fvec( farray, farray+5 );

    int imax = max( max( ivec ), max( iarray, 7 ));
    float fmax = max( max( fvec ), max( farray, 5 ));
    string smax = max( max( svec ), max( sarray, 6 ));

	cout << "imax should be 169  -- found: " << imax << "\n"
	     << "fmax should be 24.8 -- found: " << fmax << "\n"
		 << "smax should be were -- found: " << smax << "\n";
}

int main()
{
    ex2_1();
	// ex2_2();
    // ex2_3();
	// ex2_4();
	// ex2_5();
}

bool fibon_elem( int pos, int &elem )
{
	if ( pos <= 0 || pos > 1024 ) 
   {  
        // invalid position in our implementation
        // elem is set to 0 in the off chance 
        // that the user ignores the return value
        elem = 0;
        return false;
   }

   elem = 1; 
   int n_2 = 1, n_1 = 1;
   for ( int ix = 3; ix <= pos; ++ix ) 
   {
		 elem = n_2 + n_1;
		 n_2 = n_1; n_1 = elem;
   }   
   return true;
}

bool calc_elements( vector<int> &vec, int pos ) 
{
   if ( pos <= 0 || pos > 64 )
   {
        cerr << "Sorry. Invalid position: "
             << pos << endl;
        return false;
   }

   for ( int ix = vec.size()+1; ix <= pos; ++ix ){
	     // cout << "ix : " << ix << " == " << (ix*(3*ix-1))/2 << endl;
         vec.push_back( (ix*(3*ix-1))/2 );
   }

   return true;
}

void display_elems( vector<int> &vec, const string &title,
                    ostream &os )
{
   os << '\n' << title << "\n\t";
   for ( int ix = 0; ix < vec.size(); ++ix ) 
	     os << vec[ ix ] << ' ';
   os << endl;
}

void really_calc_elems( vector<int> &vec, int pos )
{
	for ( int ix = vec.size()+1; ix <= pos; ++ix ){
	      cout << "ix : " << ix << " == " << (ix*(3*ix-1))/2 << endl;
          vec.push_back( (ix*(3*ix-1))/2 );
	}
}

bool pentagonal_elem( int pos, int &elem )
{
    if ( ! check_validity( pos )){
		 cout << "Sorry. Invalid position: " << pos << endl;
         elem = 0;
		 return false;
	 }

    const vector<int> *pent = pentagonal_series( pos );
    elem = (*pent)[pos-1];
    return true;
}

const vector<int>*
pentagonal_series( int pos )
{
    static vector<int> _elems;
    if ( check_validity( pos ) && ( pos > _elems.size() ))
    {	
         for ( int ix = _elems.size()+1; ix <= pos; ++ix ) {
// cout << "ix: " << ix << " == " << (ix*(3*ix-1))/2 << endl;
               _elems.push_back( (ix*(3*ix-1))/2 );
		 }
     }
   return &_elems;
}

