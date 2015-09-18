#include "range_based_for_loop.h"
NS_BEGIN(elloop)
NS_BEGIN(range_based_for_loop)

TEST(RangeFor, Usage) {
	// array type.
	int ary[] {1, 2, 3, 4, 5};
	for (auto i:ary) {
		psln(i);
	}

	// stl containers.
	std::vector<int> vec{ 1, 2, 3, 4, 5 };
	for (auto e : vec) {
		psln(e);
	}


}

NS_END(range_based_for_loop)
NS_END(elloop)