#include <iostream>
#include <sstream>
#include <locale>
using namespace std;

int main()
{
	locale loc;
	const time_get<char> & tg = use_facet< time_get<char> > (loc);
	int idx = tg.date_order(); 
	char * message[] = {"no_order","dmy","mdy","ymd","ydm"};
	cout << loc.name() << endl << "date order " << message[idx] << endl;

	ios::iostate  state=0;   
	istringstream  iss("10:26:00");
	istreambuf_iterator<char> itbegin(iss); 
	istreambuf_iterator<char> itend;  
	tm  time;
	tg.get_time(itbegin, itend, iss, state, & time); 
	cout << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec << endl;
}
	

