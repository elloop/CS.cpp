#include "inc.h"

BEGIN_TEST(TupleTest, Basic, @);
	std::tuple<int, int, int> x;
	
	std::string s("");
	psln(s);
END_TEST;