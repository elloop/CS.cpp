#include "inc.h"
#include <algorithm>

BEGIN_TEST(TupleTest, Basic, @);
	std::tuple<int, int, int> x;
	
	std::string s("");

	psln(s);
END_TEST;

BEGIN_TEST(TupleTest, Get, @);


std::tuple<int, int, int> x;


std::get<0>(x);

END_TEST;