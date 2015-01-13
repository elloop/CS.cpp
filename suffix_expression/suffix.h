/*
 * =====================================================================================
 *
 *       Filename:  suffix.h
 *
 *    Description:  convert a prefix expr to mid-fix expr
 *
 *        Version:  1.0
 *        Created:  2014年03月25日 19时19分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  elloop (), elloop@foxmail.com
 *   Organization:  China
 *
 * =====================================================================================
 */


#ifndef  SUFFIX_EXPR_INC
#define  SUFFIX_EXPR_INC
#include <string>
class SuffixTest {
public:
	void test();
	std::string suffix2midfix ( std::string & suffixStr );
private:
	bool _isFirstOpPriorityHigher(char, char);
	enum OpType {
		NUM,
		OP,
		LEFT_BRACKET,
		RIGHT_BRACKET,
	};
	OpType _fectchAElement(char elem);
};
#endif   /* ----- #ifndef SUFFIX_EXPR_INC  ----- */
