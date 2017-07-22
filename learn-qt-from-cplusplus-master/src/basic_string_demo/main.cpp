#include <string>
#include <iostream>
using namespace std;
int main()
{
	basic_string<char> s1;
	basic_string<char> s2 ("hello world");
	basic_string<char> s3 ("hello world", 5);
	basic_string<char> s4 ( s2, 6);
	cout << s1 << endl << s2 << endl << s3 << endl << s4 << endl;

	basic_string<wchar_t> ws (L"µÃÓÑÄÑÊ§ÓÑÒ×(A friend is easier lost than found)");
	wcout.imbue(locale("chs"));
	wcout << "size is: " << sizeof(ws[7]) << endl << ws << endl; 


}