#include "c_lib_test.h"
#include <ctime>

NS_BEGIN(elloop);
NS_BEGIN(c_lib_test);

TEST(CLibTest, TimeTest) {
	pcln("CLibTest ---> TimeTest");

	time_t timeVar;
	time(&timeVar);
	char * ctimeStr = ctime(&timeVar);
	psln(ctimeStr);

	typedef int IInt;
	IInt i = 100;
	psln(i);
	typedef int IInt;
	IInt ii = 10000;
	psln(ii);
}

NS_END(c_lib_test);
NS_END(elloop);
