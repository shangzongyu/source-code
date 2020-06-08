/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class LibMat {
public:
	LibMat(){
		cout << "LibMat::LibMat() default constructor!\n";
	}
	
	virtual ~LibMat(){
		cout << "LibMat::~LibMat() destructor!\n";
	}

	virtual void print() const {
		cout << "LibMat::print() -- I am a LibMat object!\n";
	}
};

class Book : public LibMat {
public:
	Book( const string &title, const string &author )
		: _title( title ), _author( author ){
		cout << "Book::Book( " << _title
			 << ", " << _author << " )  constructor\n";
	}

	~Book(){
		cout << "Book::~Book() destructor!\n";
	}

	virtual void print() const {
		cout << "Book::print() -- I am a Book object!\n"
			 << "My title is: " << _title << '\n'
			 << "My author is: " << _author << endl;
	}

	const string& title() const { return _title; }
	const string& author() const { return _author; }

protected:
	string _title;
	string _author;
};

class AudioBook : public Book {
public:
	AudioBook( const string &title, 
		       const string &author, const string &narrator )
		: Book( title, author ), _narrator( narrator ){
		cout << "AudioBook::AudioBook( " << _title
			 << ", " << _author 
			 << ", " << _narrator
			 << " )  constructor\n";
	}

	~AudioBook(){
		cout << "AudioBook::~AudioBook() destructor!\n";
	}

	virtual void print() const {
		cout << "AudioBook::print() -- I am a AudioBook object!\n"
			 << "My title is: " << _title << '\n'
			 << "My author is: " << _author << '\n'
			 << "My narrator is: " << _narrator << endl;
	}

	const string& narrator() const { return _narrator; }

protected:
	string _narrator;
};

void print( const LibMat &mat )
{
	cout << "in global print(): about to print mat.print()\n";
	mat.print();
}

int main()
{

	// objects are in local blocks to force destruction
	{   
        cout << "\n" << "Creating a LibMat object to print()\n";
  	    LibMat m;
	    print( m );
	}

	{
        cout << "\n" << "Creating a Book object to print()\n";
	    Book b( "The Castle", "Franz Kafka" );
	    print( b );
	}
	
	{
        cout << "\n" << "Creating a AudioBook object to print()\n";
	    AudioBook ab( "Man Without Qualities", "Robert Musil", "Kenneth Meyer" );
	    print( ab );
	}

	return 0; // unnecessary but quiets vc++
}

