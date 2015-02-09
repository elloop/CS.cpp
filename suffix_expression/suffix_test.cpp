#include "suffix.h"
#include "inc.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;

int main ( int argc, char * argv[] ) {
	clock_t begin, end;
	begin = clock();
	pc ( argv[0] );
	/****************************** begin *************************************/

	SuffixTest suffix;
	suffix.test();

	/****************************** end *************************************/
	end = clock();
	cout << "time consumed: " << setprecision ( 4 ) << fixed << ( double ) ( end - begin ) / CLOCKS_PER_SEC << "s" << endl;
	return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
