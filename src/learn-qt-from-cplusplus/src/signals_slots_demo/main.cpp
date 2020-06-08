#include "signals_slots_declare.h"

int main()
{
	A  a;
	B  b;
	QObject::connect( & a, SIGNAL(stateChanged(int)), 
					  & b, SLOT(process(int) ) );
	a.setValue(100);
	return 0;
}
