#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(thread_test)

class Task {
public:

	int _id;
	int _size;
};

NS_END(thread_test)
NS_END(elloop)