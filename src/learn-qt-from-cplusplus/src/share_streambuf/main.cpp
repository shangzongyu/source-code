#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	ofstream dec_stream( "demo.txt" );
	ostream  hex_stream( dec_stream.rdbuf() );

	hex_stream << hex << showbase;
	int a[4] = {12, 34, 56, 78};
	for (int i=1; i<4; i++){
		dec_stream << a[i];
		hex_stream << "[" << a[i] << "] ";
	}
	return 0;
}