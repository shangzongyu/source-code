#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
int main()
{
	ifstream fs("hong_lou_meng.txt");
	stringstream ss;
	ss << fs.rdbuf();
	string str = ss.str();
	
	string::size_type pos = str.rfind("קל׃ס");
	
	ss.seekg(pos);
	string one_line;  
	getline(ss, one_line);
	cout << one_line << endl;
	
	return 0;
}