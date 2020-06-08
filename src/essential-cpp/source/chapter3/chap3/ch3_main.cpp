/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// globals as convenience for executing procedures
const int int_size = 12;
const int string_size = 4;
const int int_not_present = 1024;

int    ia[int_size]    = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
string sa[string_size] = { "pooh", "piglet", "eeyore", "tigger" };

vector<int> ivec( ia, ia+int_size );
vector<string> svec( sa, sa+string_size );

// iterative versions of find() in Section 3.1
const int* find_ver1( const vector<int> &vec, int value )
{
    for ( int ix = 0; ix < vec.size(); ++ix )
   if ( vec[ ix ] == value )
        return &vec[ ix ];
    return 0;
} 

template <typename elemType>
const elemType* 
find_ver2( const vector<elemType> &vec, 
           const elemType &value )
{
    for ( int ix = 0; ix < vec.size(); ++ix )
          if ( vec[ ix ] == value )
               return &vec[ ix ];

    return 0;
}

template <typename elemType>
inline const elemType* 
begin( const vector<elemType> &vec )
	 { return vec.empty() ? 0 : &vec[0]; }

template <typename elemType>
inline const elemType* 
end(  const vector<elemType> &vec )
	{ return vec.empty() ? 0 : &vec[vec.size()]; }

template <typename elemType>
const elemType* 
find_ver3( const elemType *array, int size, 
           const elemType &value )
{
	if ( ! array || size < 1 )
         return 0;

   for ( int ix = 0; ix < size; ++ix )
			// we can apply subscript operator to pointer
         if ( array[ ix ] == value )
              return &array[ ix ];

   return 0; // value not found
}

template <typename elemType>
const elemType* 
find_ver4( const elemType *array, int size, 
           const elemType &value )
{
	if ( ! array || size < 1 ) return 0;

   // ++array increments array by one elememt
   for ( int ix = 0; ix < size; ++ix, ++array )
         // *array dereferences the address
         if ( *array == value )
              return array;
   return 0;
}

template <typename elemType>
const elemType* 
find_ver5( const elemType *first, 
           const elemType *last, const elemType &value )
{
	if ( ! first || ! last )
        return 0;

   // while first does not equal last,
   // compare value with element addressed by first 
   // if the two are equal, return first
   // otherwise, increment first to address next element

   for ( ; first != last; ++first )
         if ( *first == value )
              return first;

   return 0;
}

// Section 3.2 version of find
template <typename IteratorType, typename elemType >
IteratorType 
find_ver6( IteratorType first, IteratorType last, 
           const elemType &value )
{
	for ( ; first != last; ++first )
		  if ( value == *first )
               return first;

   return last;
}

void prog_find_vers()
{
    const int *iptr = find_ver1( ivec, ivec[2] );
	if ( iptr != &ivec[2] )
		 cerr << "?? find_ver1 failed!\n";
	else cerr << "!! find_ver1 ok!\n";

	const string* sptr = find_ver2( svec, svec[2] );
	if ( sptr != &svec[2] )
		 cerr << "?? find_ver2 failed with string!\n";
	else cerr << "!! find_ver2 ok with string!\n";

	iptr = find_ver2( ivec, ivec[2] );
	if ( iptr != &ivec[2] )
		 cerr << "?? find_ver2 failed with int!\n";
	else cerr << "!! find_ver2 ok with int!\n";

	iptr = find_ver3( ia, int_size, ia[2] );
	if ( iptr != &ia[2] )
		 cerr << "?? find_ver3 failed with int array!\n";
	else cerr << "!! find_ver3 ok with int array!\n";

	sptr = find_ver3( sa, string_size, sa[2] );
	if ( sptr != &sa[2] )
		 cerr << "?? find_ver3 failed with string array!\n";
	else cerr << "!! find_ver3 ok with string array!\n";

	iptr = find_ver4( begin( ivec ), ivec.size(), ivec[2] );
	if ( iptr != &ivec[2] )
		 cerr << "?? find_ver4 failed with int vector!\n";
	else cerr << "!! find_ver4 ok with int vector!\n";

	sptr = find_ver4( begin( svec ), svec.size(), svec[2] );
	if ( sptr != &svec[2] )
		 cerr << "?? find_ver4 failed with string vector!\n";
	else cerr << "!! find_ver4 ok with string vector!\n";

	sptr = find_ver5( sa, sa+string_size, sa[2] );
	if ( sptr != &sa[2] )
		 cerr << "?? find_ver5 failed with string array!\n";
	else cerr << "!! find_ver5 ok with string array!\n";

	iptr = find_ver5( begin( ivec ), end( ivec ), ivec[2] );
	if ( iptr != &ivec[2] )
		 cerr << "?? find_ver5 failed with int vector!\n";
	else cerr << "!! find_ver5 ok with int vector!\n";

	iptr = find_ver5( begin( ivec ), end( ivec ), int_not_present );
	if ( iptr != 0 )
		 cerr << "?? find_ver5 failed with int not present in vector!\n";
	else cerr << "!! find_ver5 ok with int not present in vector!\n";

	sptr = find_ver6( sa, sa+string_size, sa[2] );
	if ( sptr != &sa[2] )
		 cerr << "?? find_ver6 failed with string array and iterators!\n";
	else cerr << "!! find_ver3 ok with string array and iterators!\n";

	vector< int >::iterator it;	
	it = find_ver6(  ivec.begin(), ivec.end(), ivec[2] );
	if ( *it != ivec[2] )
		 cerr << "?? find_ver6 failed with int vector and iterators!\n";
	else cerr << "!! find_ver4 ok with int vector and iterators!\n";
}

// from Section 3.6: How to Design a Generic Algorithm

vector<int> 
less_than_10( const vector<int> &vec )
{
    vector<int> nvec;
    for ( int ix = 0; ix < vec.size(); ++ix )
          if ( vec[ ix ] < 10 )
               nvec.push_back( vec[ ix ] );
    return nvec;
}

bool less_than( int v1, int v2 ) 
     { return v1 < v2 ? true : false; }

bool greater_than( int v1, int v2 ) 
     { return v1 > v2 ? true : false; }

vector<int> 
filter_ver1( const vector<int> &vec, 
             int filter_value, 
             bool (*pred)( int, int ))
{
    vector<int> nvec;

    for ( int ix = 0; ix < vec.size(); ++ix )
          // invokes the function addressed by pred
          // tests element vec[ix] against filter_value
          if ( pred( vec[ ix ], filter_value ))
               nvec.push_back( vec[ ix ] );

    return nvec;
}

vector<int> 
filter_ver2( const vector<int> &vec, 
             int val, less<int> &lt )
{
    vector<int> nvec;
    vector<int>::const_iterator iter = vec.begin();
    
    // bind2nd( less<int>, val )
    // binds val to the second value of less<int>
    // less<int> now compares each value against val

    while (( iter = 
             find_if( iter, vec.end(), 
                      bind2nd( lt, val ))) != vec.end() )
    {
             // each time iter != vec.end(), 
             // iter addresses an element less than val
             nvec.push_back( *iter );
             iter++;
    }
    return nvec;
}

template <typename InputIterator, typename OutputIterator,
		  typename ElemType,      typename Comp>
OutputIterator 
filter_ver3( InputIterator first, InputIterator last,
             OutputIterator at,   const ElemType &val, Comp pred )
{
    while (( first = 
             find_if( first, last, 
                      bind2nd( pred, val ))) != last )
             // assign value, then advance both iterators
             *at++ = *first++;
    return at;
}

vector<int> sub_vec( const vector<int> &vec, int val )
{ 
    vector<int> local_vec( vec );
    sort( local_vec.begin(), local_vec.end() );

    vector<int>::iterator iter =
          find_if( local_vec.begin(), 
                   local_vec.end(),
                   bind2nd( greater<int>(), val ));

    local_vec.erase( iter, local_vec.end() );
    return local_vec;
}

void prog_filter_vers()
{
	const int solution_size = 6;

    vector<int> local_vec = less_than_10( ivec );
	if ( local_vec.size() != solution_size )
		 cerr << "?? less_than_10 failed! expected expected "
		      << solution_size << ", received: " 
		      << local_vec.size() << endl;
	else cerr << "!! less_than_10 ok!\n";

	const int partition_value = 10;
	local_vec = filter_ver1( ivec, partition_value, greater_than );

	if ( local_vec.size() != solution_size )
		 cerr << "?? filter_ver1 failed! expected expected "
		      << solution_size << ", received: "  
		      << local_vec.size() << endl;
	else cerr << "!! filter_ver1 ok!\n";

	local_vec = filter_ver2( ivec, partition_value, less<int>() );
	if ( local_vec.size() != solution_size )
		 cerr << "?? filter_ver2 failed! expected "
		      << solution_size << ", received: " 
		      << local_vec.size() << endl;
	else cerr << "!! filter_ver2 ok!\n";

    // unless we use an iserter, must provide a sized container
	// within which filter can assign the values ...
	int ia2[ solution_size ];
	filter_ver3( ia, ia+int_size, ia2, partition_value, less<int>() );

	int err_cnt = 0;
	for ( int ix = 0; ix < solution_size; ++ix )
		  if ( ia[ ix ] != ia2[ ix ] )
			   ++err_cnt;

	if ( err_cnt )
		 cerr << "?? filter_ver3 failed for array! "
		      << err_cnt << " unexpected values\n";
	else cerr << "!! filter_ver3 for array ok!\n";

	vector<int> ivec2( solution_size );
	filter_ver3( ivec.begin(), ivec.end(), ivec2.begin(), 
                 partition_value, greater<int>() );

	err_cnt = 0;
	ix = solution_size;

	for ( int iy = 0; ix < ivec.size(); ++ix, ++iy )
		  if ( ivec[ ix ] != ivec2[ iy ] )
			   ++err_cnt;

	if ( err_cnt )
		 cerr << "?? filter_ver3 failed for vector! "
		      << err_cnt << " unexpected values\n";
	else cerr << "!! filter_ver3 for vector ok!\n";

	// illustrate using an inserter
	vector<int> ivec3;
	filter_ver3( ivec.begin(), ivec.end(), back_inserter( ivec3 ), 
                 partition_value, greater<int>() );

	if ( ivec3.size() != solution_size )
		 cerr << "?? filter_ver3 with back inserter failed! expected "
		      << solution_size << ", received: " 
		      << ivec3.size() << endl;
	else cerr << "!! filter_ver3 with back inserter ok!\n";

	ivec3 = sub_vec( ivec, partition_value );
	if ( ivec3.size() != solution_size )
		 cerr << "?? sub_vec failed! expected "
		      << solution_size << ", received: " 
		      << ivec3.size() << endl;
	else cerr << "!! sub_vec ok!\n";
}

// Section 3.10 iostream_iterator examples	

void prog_io_std()
{
	cout << "please enter some text, then indicate end of file!\n";

	istream_iterator< string > is( cin );
	istream_iterator< string > eof;

    vector< string > text;
    copy( is, eof, back_inserter( text ));

	sort( text.begin(), text.end() );

	ostream_iterator<string> os( cout, " " );
    copy( text.begin(), text.end(), os );
}


void prog_io_fil()
{
   ifstream in_file( "input_file.txt" );
   ofstream out_file( "output_file.txt" );

   if ( ! in_file || ! out_file ) {
        cerr << "?? unable to open the necessary files.\n";
		return;
   } 
   else cerr << "!! ok: input and output files opened!\n";

   istream_iterator< string > is( in_file );
   istream_iterator< string > eof;

   vector< string > text;
   copy( is, eof, back_inserter( text ));

   if ( text.empty() )
	    cerr << "?? iostream iterators failed: string vector empty!\n";
   else cerr << "!! iostream iterators seem to work: "
             << text.size() << " strings read in!\n";

   sort( text.begin(), text.end() );

   ostream_iterator<string> os( out_file, " " );
   unique_copy( text.begin(), text.end(), os );
}

void prog_io_iters()
{
	// prog_io_std();
	prog_io_fil();
}

int main()
{
	cerr << "About to execute prog_find_vers()\n\n";
	prog_find_vers();

	cerr << "\n\nAbout to execute prog_filter_vers()\n\n";
    prog_filter_vers();

	cerr << "\n\nAbout to execute prog_io_iters()\n\n";
	prog_io_iters();

	cerr << "\n\nOk -- done!\n\n";
	return 0; // quiet vc6++
}