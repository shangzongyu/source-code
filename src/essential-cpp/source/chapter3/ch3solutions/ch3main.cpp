#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <iterator>

using namespace std;

typedef vector<string> vstring;

void initialize_exclusion_set( set<string>& );
void process_file( map<string,int>&, const set<string>&, ifstream& );
void user_query( const map<string,int>& );
void display_word_count( const map<string,int>&, ofstream& );
vector<int> sub_vec( const vector<int>&, int, less<int>& );

void populate_map( ifstream&, map<string,vstring> &families);
void display_map( const map<string,vstring> &families, ostream &os = cout );
void query_map( const string &family, const map<string,vstring> &families );


template <typename elemType>
void display_vector( const vector<elemType> &vec,
                     ostream &os=cout, int len= 8 )
{
	 vector<elemType>::const_iterator 
               iter = vec.begin(), 
               end_it = vec.end();

    int elem_cnt = 1;
    while ( iter != end_it ) 
		    os << *iter++
               << ( !(elem_cnt++ % len ) ? '\n' : ' ');
    os << endl;
}

template <typename InputIterator,
          typename OutputIterator,
		  typename ElemType,
          typename Comp>
OutputIterator 
filter( InputIterator first, InputIterator last,
        OutputIterator at, 
        const ElemType &val, Comp pred )
{
    while (( first = 
             find_if( first, last, 
                      bind2nd( pred, val ))) != last )
	{
			 cout << "found value: " << *first << endl;
             // assign value, then advance both iterators
             *at++ = *first++;
    }
    return at;
}

void ex_filter()
{

	const int elem_size = 8;

	int ia[ elem_size ] = { 12, 8, 43, 0, 6, 21, 3, 7 };
	vector<int> ivec( ia, ia+elem_size );

	int ia2[ elem_size ];
	vector<int> ivec2;

	cout << "filtering integer array for values less than 8\n";
	filter( ia, ia+elem_size, ia2, elem_size, less<int>() );

	cout << "filtering integer vector for values greater than 8\n";
	filter( ivec.begin(), ivec.end(), back_inserter( ivec2 ), elem_size, greater<int>() );
}


void ex3_1()
{
    ifstream ifile( "MooCat.txt" );
	ofstream ofile( "MooCat.map" );

    if ( !  ifile || ! ofile ){
         cerr << "Unable to open file -- bailing out!\n";
         return;
    }

    set<string> exclude_set;
    initialize_exclusion_set( exclude_set );

    map<string,int> word_count;
    process_file( word_count, exclude_set, ifile );
    user_query( word_count );
    display_word_count( word_count, ofile );
}

class LessThan {
public:
	bool operator()( const string &s1, const string &s2 ) 
	               { return s1.size() < s2.size(); }
};

void ex3_2()
{
    ifstream ifile( "MooCat.txt" );
	ofstream ofile( "MooCat.sort" );

    if ( !  ifile || ! ofile ){
         cerr << "Unable to open file -- bailing out!\n";
         return;
    }

	vector<string> text;
    string word;

    while ( ifile >> word ) {
		    cout << word << ' ';
            text.push_back( word );
	}
    cout << "\n\n";

	sort( text.begin(), text.end(), LessThan() );

	for ( vector<string>::iterator it = text.begin();
	      it != text.end(); ++it )
			  cout << *it << ' ';
    cout << endl;

	display_vector( text, ofile );
}

void ex3_3()
{
    map< string, vstring > families;

	ifstream nameFile( "families.txt" );
	if ( !  nameFile ) {
			cerr << "Unable to find families.txt file. Bailing Out!\n";
			return;
	}

    populate_map( nameFile, families );

    string family_name;
    while ( 1 )
	{ 
		cout << "Please enter a family name or q to quit ";
		cin >> family_name;
		if ( family_name == "q" )
			 break;
        query_map( family_name, families );
	}
	display_map( families );
}

class even_elem {
public:
	bool operator()( int elem ) 
         { return elem%2 ? false : true; }
};

void ex3_4()
{
	vector< int > input;
	istream_iterator<int> in( cin ), eos;

	ofstream even_file( "even_file" ), 
              odd_file( "odd_file"  );

	if ( ! even_file || ! odd_file ){ 
         cerr << "arghh!! unable to open the output files. bailing out!";
	     return ;
	}

	copy( in, eos, back_inserter( input ));
	vector<int>::iterator division =
               partition( input.begin(), input.end(), even_elem() );

	ostream_iterator<int> even_iter( even_file, "\n" ), 
                           odd_iter( odd_file, " "  );

	copy( input.begin(), division, even_iter );
	copy( division, input.end(), odd_iter );

}


int main()
{
    // ex_filter();
	// ex3_1();
	// ex3_2();
	// ex3_3();
	ex3_4();
}

vector<int> sub_vec( const vector<int> &vec, 
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

             // each time iter != vec.end(), 
             // iter addresses an element less than val

             nvec.push_back( *iter );

    return nvec;
}
  
void initialize_exclusion_set( set<string> &exs ){
     static string _excluded_words[26] = {
          "the","and","but","that","then","are","been",
          "can","a","could","did","for", "of",
          "had","have","him","his","her","its","is", 
          "were","which","when","with","would"
     };

    exs.insert( _excluded_words, _excluded_words+26 );
}

void process_file( map<string,int> &word_count, 
                   const set<string> &exclude_set,
                   ifstream &ifile )
{
    string word;

    while ( ifile >> word ){
       // if word is within set, skip
       if ( exclude_set.count( word ))
            continue; 

       word_count[ word ]++;
    }
}

void user_query( const map<string,int> &word_map )
{
    string search_word;
    cout << "Please enter a word to search: q to quit ";
    cin >> search_word;
    while ( search_word.size() && search_word != "q" )
    {
            map<string,int>::const_iterator it;
            if (( it = word_map.find( search_word )) 
				       != word_map.end() )
                 cout << "Found! "  << it->first
                      << " occurs " << it->second
                      << " times.\n";
              else cout << search_word 
                        << " was not found in text.\n";
              cout << "\nAnother search? (q to quit) ";
              cin >> search_word;
      }
}
		
void display_word_count( const map<string,int> &word_map, ofstream &os )
{
	 map<string,int>::const_iterator 
               iter = word_map.begin(), 
               end_it = word_map.end();

	 while ( iter != end_it ) {
            os << iter->first  << " ( "
               << iter->second << " )" << endl;
			++iter;
	 }
     os << endl;
}

void populate_map( ifstream &nameFile,
				   map<string,vstring> &families )
{
	string textline;
	while ( getline( nameFile, textline, '\n' ))
	{
   	    string fam_name;
	    vector<string> child;
		cout << "textline: " << textline << endl;

	    string::size_type pos = 0, prev_pos = 0, 
			              text_size = textline.size();

		if ( ! text_size )
			 continue;

        // ok: find each word separated by a space
   	    while ((  pos = textline.find_first_of( ' ', pos )) 
                     != string::npos )
		{
		    string::size_type end_pos = pos-prev_pos;
		    if ( ! prev_pos )
			     fam_name = textline.substr( prev_pos, end_pos  );
		    else child.push_back(textline.substr(prev_pos,end_pos));
			prev_pos = ++pos;
		}
     
		// now handle last child
		if ( prev_pos < text_size )
			 child.push_back(textline.substr(prev_pos,pos-prev_pos)); 

		cout << "family name: " << fam_name
			 << " children: "   << child.size() << endl;

	    if ( ! families.count( fam_name ))
	         families[ fam_name ] = child;
        else cerr << "Oops! We already have a "
                  << fam_name << " family in our map!\n";
	}
}

void display_map( const map<string,vstring> &families, ostream &os )
{
	map< string, vstring >::const_iterator 
			     it = families.begin(), 
                 end_it = families.end();

	while ( it != end_it )
	{
		    os << "The "
			   << it->first  // print out family name
			   << " family ";

			if ( it->second.empty() )
			     os << "has no children\n";
            else 
			{  // print out vector of children
                os   << "has " << it->second.size() 
                     << " children: ";

			    vector< string >::const_iterator 
                        iter = it->second.begin(),
                        end_iter = it->second.end();
			      
			    while ( iter != end_iter ) 
				      { os << *iter << " "; ++iter; }
				os << endl;
			}

			++it;
	}
}

void query_map( const string &family, const map<string,vstring> &families ) 
{
	map<string,vstring>::const_iterator it = families.find( family );
	if ( it == families.end() ) 
	{
		 cout << "Sorry. The "
			  << family << " family is not currently entered.\n";
		return;
	}
		
	cout << "The " << family << " family "; 
    if ( ! it->second.size() )
		 cout << " has no children\n";
	else 
    {     // print out vector of children
          cout << " has " << it->second.size() 
               << " children: ";

		  vector< string >::const_iterator 
                    iter = it->second.begin(),
                    end_iter = it->second.end();
			      
		  while ( iter != end_iter ) 
			    { cout << *iter << " "; ++iter; }
		  cout << endl;
	}
}