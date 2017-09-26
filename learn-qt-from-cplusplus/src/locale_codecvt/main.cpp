#include <iostream>
#include <locale>
using namespace std;

int main ()
{
	typedef codecvt<wchar_t,char,mbstate_t> cvt_type;

	locale loc;
	const cvt_type & cvt = use_facet< cvt_type >(loc);

	const int size = 20;
	const char *p1, src[size] = "hello world!";
	wchar_t    *p2, dst[size];

	mbstate_t state;
	cvt_type::result result = cvt.in (state,
		src, src+size, p1,
		dst, dst+size, p2 );

	if ( result == cvt_type::ok )
		wcout << dst << endl;
	return 0;
}