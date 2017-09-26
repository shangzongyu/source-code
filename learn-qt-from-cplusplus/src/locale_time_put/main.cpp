#include <iostream>
#include <sstream>
#include <locale>
using namespace std;

int main()
{
	time_t timestamp;
	time ( &timestamp );
	tm * now = localtime ( & timestamp );

	locale loc[]={locale(), locale("")};
	for (int i=0; i<2; i++) {
		const time_put<char>& tp = use_facet <time_put<char> > ( loc[i] );

		cout << loc[i].name() << " : ";
		char pattern[]="%x, %A, %p %X";
		tp.put ( cout, cout, ' ', now, pattern, pattern+sizeof(pattern)-1 );
		cout << endl;
	}
 	return 0;
}
