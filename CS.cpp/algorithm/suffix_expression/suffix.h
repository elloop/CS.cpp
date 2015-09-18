#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif

#include "inc.h"
#include <string>

NS_BEGIN(elloop)
NS_BEGIN(suffix)

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

NS_END(suffix)
NS_END(elloop)
