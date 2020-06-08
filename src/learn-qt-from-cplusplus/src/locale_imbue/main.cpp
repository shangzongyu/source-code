#include <iostream>
#include <locale>
#include <iomanip>
using namespace std;
  
int main( ) 
{
	char * region_names[] = {"australia", "austria", "belgium", "brazil", 
	"canada", "china", "denmark", "finland", "france", "germany", "greece", 
	"hong kong", "hungary", "iceland", "ireland", "italy", "japan", 
	"korea", "mexico", "netherlands", "new zealand", "norway", "poland",  
	"portugal", "russia", "singapore", "slovak", "spain", "sweden",  
	"switzerland", "taiwan", "turkey", "united kingdom", "united states"};

	double x = 12345.67;
	/*for (int i=0; i< sizeof(region_names)/sizeof(char); i++) {
		cout.imbue( locale( region_names[i] ) );
		cout << setw(15) << region_names[i] << ": " << fixed << x << endl;
	}*/
	locale loc("");

	cout << loc.name();
}

 
