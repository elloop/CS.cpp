#include "suffix.h"
#include <fstream>
#include <string>
#include "inc.h"
#include "data_structure/stack/stash.h"


NS_BEGIN(elloop)
NS_BEGIN(suffix)
using namespace std;

void SuffixTest::test() {
	string inputName ( "test-case" );
	string outputName ( "result" );
	ifstream in ( inputName.c_str(), ios::in );
	ofstream out ( outputName.c_str(), ios::out );

	if ( !in || !out ) {
		ps ( "fail to open test-case or output file" );
		return;
	}

	string line ( "" );
	string result ( "" );
	while ( getline ( in, line ) ) {
		ps ( line );
		result = suffix2midfix ( line );
		ps ( result );
		out << result << endl;
	}
	in.close();
	out.close();
	cr;
}

// example: 2*(3+5+6*7)-4+7/1 => 235+67*+*4-71/+
string SuffixTest::suffix2midfix ( string & suffixStr ) {
	// step: read the input expression
	/*
	 * 1. num : output.
	 * 2. op :
	 * 			1)  (opNew > opOld) : push into opNew into stack.
	 * 			2) !(opNew > opOld) : pop and ouput the opOld until opNew > opOld, push opNew into stack.
	 * 3. (  : push into stack.
	 * 4. )  : pop and ouput  ops until met '(' (don't output the '(' ')'.
	 * 5. end of the input: pop all ops and output them.
	 */

	Stash stack;
	string result ( "" );
	size_t pos = 0;
	while ( pos < suffixStr.size() ) {
		char elem = suffixStr[pos];
		char * head ( 0 );
		switch ( _fectchAElement ( elem ) ) {
			case NUM:
				result += elem;
				break;
			case OP:
				if ( stack.empty() ) {
					stack.push ( new char ( elem ) );
				} else {
					// newOp > oldOp, push newOp
					char * oldOpPtr = ( char * ) stack.peek();
					if ( _isFirstOpPriorityHigher ( elem, *oldOpPtr ) ) {
						stack.push ( new char ( elem ) );
					} else {
						// else, pop and output oldOp, push newOp !! a BUG: don't push directly
						// modified on 20140326 fix the bug: pop all the ops that higer or equal to newOp
						while ( !stack.empty() && !_isFirstOpPriorityHigher ( elem, *oldOpPtr ) ) {
							result += *oldOpPtr; // output ops whose priority >= newOp's
							delete ( char * ) stack.pop();
							oldOpPtr = ( char * ) stack.peek();
						}
						// push the newOp
						stack.push ( new char ( elem ) );
					}
				}
				break;
			case LEFT_BRACKET:
				stack.push ( new char ( elem ) );
				break;
			case RIGHT_BRACKET:
				// pop and output until '('
				head = ( char * ) stack.peek();
				while ( *head != '(' ) {
					result += *head; // output
					delete ( char * ) stack.pop();
					head = ( char * ) stack.peek();
				}
				// now head is '(', pop it only
				delete ( char * ) stack.pop();
				break;
			default:
				p ( "unknown" );
				cr;
				break;
		}
		++pos;
	}

	while ( !stack.empty() ) {
		char * head = ( char * ) stack.pop();
		result += *head;
		delete head;
	}

	return result;
}

// return true when op1's priority is higher than ops's; else return false.
bool SuffixTest::_isFirstOpPriorityHigher ( char op1, char op2 ) {
	// todo : check the validity of op1 and op2( ensure both are contained in '+-*/')
	if ( op2 == '(' ) {
		return true;
	}
	string higherOps ( "*/" );
	string lowerOps ( "+-" );
	bool isOp1InHigherOps = ( higherOps.find ( op1 ) != string::npos );
	bool isOp2InLowerOps = ( lowerOps.find ( op2 ) != string::npos );
	return  ( isOp1InHigherOps && isOp2InLowerOps );
}

SuffixTest::OpType SuffixTest::_fectchAElement ( char elem ) {
	// todo: ensure validity of elem
	if ( elem >= '0' && elem <= '9' ) {
		return NUM;
	} else if ( elem == '(' ) {
		return LEFT_BRACKET;
	} else if ( elem == ')' ) {
		return RIGHT_BRACKET;
	} else {
		return OP;
	}
}

NS_END(suffix)
NS_END(elloop)