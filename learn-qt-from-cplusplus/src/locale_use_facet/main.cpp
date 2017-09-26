#include <locale>
#include <iostream>
using namespace std;

int main()
{
	locale os_locale("");
	const numpunct<char> & np = use_facet< numpunct<char> > (os_locale);  //1
	cout << "number punctuation of " << os_locale.name() << endl;
	cout << np.decimal_point() << " " 
		 << np.thousands_sep() << " "
		 << np.falsename()     << " "  << np.truename() << endl;
	 
	string group = np.grouping();
	for (int i=0; i<group.length(); i++)
		cout << i << "th grouping is: " << (int)group[i] << endl;         //2
}