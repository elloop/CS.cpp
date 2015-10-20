#include "stash.h"
#include <string>
#include <fstream>

NS_BEGIN(elloop);

BEGIN_TEST(StashTest, BasicTest, @@);
return;
using std::string;
// define a stack
Stash stack;

// read from file. 

// ofstream("input", ios::out) << "one\n" << "two\n" << "three\n" << "four\n";

// ifstream input ( "input", ios::in );
// if ( !input ) {
//     pln ( "fail to open input file" );
// }
// else {
//     // read string from file & save it in the stack
//     string line ( "" );
//     while ( getline ( input, line ) ) {
//         stack.push ( new string ( line ) );
//     }
//     input.close();
// }

// read from variable.
psln(stack.empty());

pcln("inserting ... ");
stack.push(new string("one"));
stack.push(new string("two"));
stack.push(new string("three"));
stack.push(new string("four"));

psln(stack.empty());

// print string and clean up
string * pstr = 0;
while ((pstr = (string *)stack.pop()) != 0) {
    psln(*pstr);
    delete pstr;
}
psln(stack.empty());

stack.cleanup();

END_TEST;

NS_END(elloop);