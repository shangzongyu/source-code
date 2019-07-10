/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
using namespace std;

bool fibon_elem( int pos, int &elem )
{

	if ( pos <= 0 || pos > 1024 )
	{
		 cerr << "invalid position: " << pos 
			  << " -- cannot handle request!\n";

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

bool print_sequence( int pos ) 
{
	if ( pos <= 0 || pos > 1024 ){
		 cerr << "invalid position: " << pos 
			  << " -- cannot handle request!\n";
         return false; 
	}

   cout << "The Fibonacci Sequence for "
        << pos << " positions: \n\t";

   // prints “1 1” for all values except pos == 1
   switch ( pos ) {
       default:
       case 2:
			 cout << "1 ";
           // no break;
       case 1:
			 cout << "1 ";
           break;
    }

   int elem;
   int n_2 = 1, n_1 = 1;
   for ( int ix = 3; ix <= pos; ++ix ) 
   {
		 elem = n_2 + n_1;
		 n_2 = n_1; n_1 = elem;

		 // print 10 elements to a line
		 cout << elem 
			 << ( !( ix % 10 ) ? "\n\t" : " " );
   }

   cout << endl;
   return true;
}

#include <vector>

void display( vector<int> vec )
{
	for ( int ix = 0; ix < vec.size(); ++ix )
		   cout << vec[ix] << ' ';
	cout << endl;
}

void swap( int val1, int val2 )
{
	int temp = val1;
   val1 = val2;
   val2 = temp;
}

void bubble_sort( vector<int> vec )
{
	for ( int ix = 0; ix < vec.size(); ++ix )
		   for ( int jx = ix+1; jx < vec.size(); ++jx )
      			      if ( vec[ ix ] > vec[ jx ] )				  
                           swap( vec[ix], vec[jx] );			
}

void bubble_sort2( vector<int> vec )
{
	for ( int ix = 0; ix < vec.size(); ++ix )
		   for ( int jx = ix+1; jx < vec.size(); ++jx )
      			 if ( vec[ ix ] > vec[ jx ] )	
					{
                      // debugging output to 
                      //    determine when swap() is called and
                      //    what values are being passed 
				      cerr  << "about to call swap!"
					        << " ix: " << ix 
				            << " jx: " << jx << '\t'
					        << " swapping: " << vec[ix] 
					        << " with " << vec[ jx ] << endl;

						   // ok: actual swap code ...
                       swap( vec[ix], vec[jx] );
					  }
}

void swap2( int val1, int val2 )
{
	cerr << "swap( " << val1 
         << ", " << val2 << " )\n";
	int temp = val1;
    val1 = val2;
    val2 = temp;
	cerr << "after swap(): val1 " << val1 
         << "  val2: " << val2 << "\n";
}

void bubble_sort3( vector<int> vec )
{
	for ( int ix = 0; ix < vec.size(); ++ix )
		   for ( int jx = ix+1; jx < vec.size(); ++jx )
      			      if ( vec[ ix ] > vec[ jx ] )				  
                           swap2( vec[ix], vec[jx] );			
}

/* 
 * OK: by declaring val1 and val2 as references
 *     changes to the two parameters within swap()  
 *     are reflected in the objects passed to swap()
 */
void swap3( int & val1, int & val2 )
{
	 /* 
     * note that our code within swap()
     * does not change -- only the relationship
     * between the parameters of swap() and the
     * objects passed to swap() changes
     */
    int temp = val1;
    val1 = val2;
    val2 = temp;
}

void bubble_sort4( vector<int> vec )
{
	for ( int ix = 0; ix < vec.size(); ++ix )
		   for ( int jx = ix+1; jx < vec.size(); ++jx )
      			      if ( vec[ ix ] > vec[ jx ] )	{
						   cerr << "about to call swap! "
							    << "ix: " << ix << " jx: " << jx
								<< "\tswapping: " << vec[ix] 
								<< " with " << vec[ jx ] << endl;
                           swap3( vec[ix], vec[jx] );
						   display( vec );
					  }
}

void display( const vector<int> *vec )
{
    if ( ! vec ){
         cout << "display(): the vector pointer is 0\n";
         return;
    }

	for ( int ix = 0; ix < vec->size(); ++ix )
		   cout << (*vec)[ix] << ' ';

	cout << endl;
}

vector<int> fibon_seq( int size )
{
   if ( size <= 0 || size > 1024 )
   {
        cerr << "Warning: fibon_seq(): "
             << size << " not supported -- resetting to 8\n";
		  size = 8;
	}

   vector<int> elems( size );

   for ( int ix = 0; ix < size; ++ix )
		   if ( ix == 0 || ix == 1 )
				  elems[ ix ] =  1;
			else elems[ ix ] =  elems[ix-1] + elems[ix-2];

   return elems;
}

#include <fstream>

void swap( int val1, int val2, ofstream &ofil )
{
	ofil << "swap( " << val1 
         << ", " << val2 << " )\n";
	int temp = val1;
    val1 = val2;
    val2 = temp;
	ofil << "after swap(): val1 " << val1 
         << "  val2: " << val2 << "\n";
}

void bubble_sort( vector<int> &vec, ofstream &ofil )
{
	for ( int ix = 0; ix < vec.size(); ++ix )
		 for ( int jx = ix+1; jx < vec.size(); ++jx )
      			  if ( vec[ ix ] > vec[ jx ] )	
			  {
          				  ofil << "about to call swap! ix: " << ix 
                    << " jx: " << jx << "\tswapping: " 
                    << vec[ix] << " with " << vec[ jx ] << endl;

              swap( vec[ix], vec[jx], ofil );
			  }
}

void swap( int val1, int val2, ofstream *ofil=0 )
{
	if ( ofil )
	   (*ofil) << "swap( " << val1 
               << ", " << val2 << " )\n";
	int temp = val1;
    val1 = val2;
    val2 = temp;
	if ( ofil )
	   (*ofil) << "after swap(): val1 " << val1 
               << "  val2: " << val2 << "\n";
}

void bubble_sort5( vector<int> &vec, ofstream *ofil = 0 )
{
	for ( int ix = 0; ix < vec.size(); ++ix )
		 for ( int jx = ix+1; jx < vec.size(); ++jx )
      			  if ( vec[ ix ] > vec[ jx ] )	
				  {
          				  if ( ofil != 0 )
                             (*ofil) << "about to call swap! ix: " << ix 
                                     << " jx: " << jx << "\tswapping: " 
                                     << vec[ix] << " with " << vec[ jx ] << endl;
                          swap( vec[ix], vec[jx], ofil );
				  }
}

void display( const vector<int> &vec, ofstream &os )
{
	for ( int ix = 0; ix < vec.size(); ++ix )
		   os << vec[ix] << ' ';
	os << endl;
}

const vector<int>*
fibon_seq2( int size )
{
   const int max_size = 1024;
	static vector< int > elems;

   if ( size <= 0 || size > max_size ){
        cerr << "fibon_seq(): oops: invalid size: "
             << size << " -- can’t fulfill request.\n";
        return 0;
	}
   
   // if size is equal to or greater than elems.size(),
   // no calculations are necessary ... 
   for ( int ix = elems.size(); ix < size; ++ix ){
		   if ( ix == 0 || ix == 1 )
				  elems.push_back( 1 );
			else elems.push_back( elems[ix-1]+elems[ix-2] );
   }
   return &elems;
}

void prog4()
{
   int ia[ 8 ] = { 8, 34, 3, 13, 1, 21, 5, 2 };
   vector<int> vec( ia, ia+8 );

   // no debug information -- 
   // it is as if we invoked bubble_sort( vec, 0 );
   bubble_sort5( vec );
   display( vec );

   // ok: debug information generated ...
   //     the default value is not used ...
   ofstream ofil( "E:\\Programs\\chapter2\\data.txt" );
   bubble_sort5( vec, &ofil ); 
   display( vec, ofil );
}

void prog3()
{
    int ia[ 8 ] = { 8, 34, 3, 13, 1, 21, 5, 2 };
	vector<int> vec( ia, ia+8 );

	cout << "vector before sort: ";
	display( &vec ); // pass the address now

    // ...
}

void prog2()
{
    int ia[ 8 ] = { 8, 34, 3, 13, 1, 21, 5, 2 };
	vector<int> vec( ia, ia+8 );

	cout << "vector before sort: ";
	display( vec ); 
    bubble_sort( vec );
    cout << "vector after sort:  ";
	display( vec ); 
}

void prog2a()
{
    int ia[ 8 ] = { 8, 34, 3, 13, 1, 21, 5, 2 };
	vector<int> vec( ia, ia+8 );

	cout << "vector before sort: ";
	display( vec ); 
    bubble_sort2( vec );
    cout << "vector after sort:  ";
	display( vec ); 
}

void prog2b()
{
    int ia[ 8 ] = { 8, 34, 3, 13, 1, 21, 5, 2 };
	vector<int> vec( ia, ia+8 );

	cout << "vector before sort: ";
	display( vec ); 
    bubble_sort3( vec );
    cout << "vector after sort:  ";
	display( vec ); 
}

void prog2c()
{
    int ia[ 8 ] = { 8, 34, 3, 13, 1, 21, 5, 2 };
	vector<int> vec( ia, ia+8 );

	cout << "vector before sort: ";
	display( vec ); 
    bubble_sort4( vec );
    cout << "vector after sort:  ";
	display( vec ); 
}

void prog1()
{
   int pos;

   cout << "Please enter a position: ";
   cin >> pos;
    
   // elem will hold the element’s value
   int elem;

   if ( fibon_elem( pos, elem ))
        cout << "element # " << pos 
             << " is " << elem << endl;
   else 
        cout << "Sorry. Could not calculate element # "
             << pos << endl;

   print_sequence( pos );

}

int main()
{
	prog1();
	// prog2();
	// prog2a();
	// prog2b();
	// prog2c();
	// prog3();
	// prog4();

	return 0; // to quiet vc6++
}