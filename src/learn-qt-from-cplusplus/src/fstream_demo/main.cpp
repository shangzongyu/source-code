#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	fstream fs("data\\test.txt", ios_base::in | ios_base::out | ios_base::app);
	if ( !fs ) {
		cerr << "cannot open test.txt"; exit(-1);
	}
	fs << "hello, world\n";
	
	fs.seekg(0);
	string s;
	fs >> s;
	cout << s;
}