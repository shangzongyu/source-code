/**************************************************
 * Essential C++ -- Stanley Lippman
 * Addison-Wesley 
 * ISBN 0-201-48518-4
 * homepage: www.objectwrite.com
 * email: slippman@objectwrite.com
 *************************************************/

#include <iostream>
#include <string>
using namespace std;

#include "ch1.h"

int main()
{
	user_profile up;

	if ( greet_user( &up ) )
	{
		 play_game( &up );
		 display_statistics( &up );
	}

	return 0;
}




