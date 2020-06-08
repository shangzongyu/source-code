#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
int main () 
{
	ifstream file("butterfly.mp3", ios::in|ios::binary|ios::ate);
	long size = file.tellg();
	file.seekg (0, ios::beg);
	char * buffer = new char [size];
	file.read (buffer, size);
	file.close();
	cout << size << " bytes read into a buffer" << endl;
	delete[] buffer;

	ifstream ifs("butterfly.mp3", ios::in|ios::binary);
	ostringstream ss;
	ss << ifs.rdbuf();
	string data = ss.str();
	cout <<data.length() << " bytes read into a string object" << endl;
	return 0;
}