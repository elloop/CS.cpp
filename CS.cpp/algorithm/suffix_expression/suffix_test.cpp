#include "suffix.h"
#include "inc.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "gtest/gtest.h"

NS_BEGIN(elloop)
NS_BEGIN(suffix)


TEST(SuffixTesting, BasicTest) {
	SuffixTest suffix;
	suffix.test();
}

NS_END(suffix)
NS_END(elloop)
