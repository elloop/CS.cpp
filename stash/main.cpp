#include <iostream>
#include <string>
#include <fstream>
#include "stash.h"
#include "string-util.h"
using namespace std;
int main ( int argc, char * argv[] ) {
	// define a stack
	Stash stack;

	ifstream input ( "input", ios::in );
	if ( !input ) {
		pln ( "fail to open input file" );
	}

	// read string from file & save it in the stack
	string line ( "" );
	while ( getline ( input, line ) ) {
		stack.push ( new string ( line ) );
	}
	input.close();

	ps(stack.empty());

	// print string and clean up
	string * pstr = 0;
	while ( ( pstr = ( string * ) stack.pop() ) != 0 ) {
		ps ( *pstr );
		delete pstr;
	}
	ps(stack.empty());
	stack.cleanup();

	return 0;
}
