#include <iostream>
#include <string>
#include <fstream>
#include "stash.h"
#include "common/print_util.h"
#include "common/inc.h"

USING_NS_STD;
USING_NS_TEST;

int main ( int argc, char * argv[] ) {
	// define a stack
	Stash stack;

	ifstream input ( "input", ios::in );
	if ( !input ) {
		pln ( "fail to open input file" );

        const char * strs[] = {"one", "two", "three", "four", "five", "six", "seve"};
        
        for ( int i=0; i<sizeof (strs) / sizeof (strs[0]); ++i ) {
            stack.push( new string(strs[i]));
        }
	}
    else {
        // read string from file & save it in the stack
        string line ( "" );
        while ( getline ( input, line ) ) {
            stack.push ( new string ( line ) );
        }
        input.close();
    }

    pcln("new make");

	psln(stack.empty());

	// print string and clean up
	string * pstr = 0;
	while ( ( pstr = ( string * ) stack.pop() ) != 0 ) {
		psln ( *pstr );
		delete pstr;
	}
	psln(stack.empty());
	stack.cleanup();

	return 0;
}
