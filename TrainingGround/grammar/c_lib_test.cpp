#include "c_lib_test.h"
#include <ctime>

NS_BEGIN(elloop);
NS_BEGIN(c_lib_test);

<<<<<<< HEAD
BEGIN_TEST(CLibTest, TimeTest, @)
	pcln("CLibTest ---> TimeTest");
=======
BEGIN_TEST(CLibTest, TimeTest, @);
pcln("CLibTest ---> TimeTest");
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340

time_t timeVar;
time(&timeVar);
char * ctimeStr = ctime(&timeVar);
psln(ctimeStr);

<<<<<<< HEAD
	typedef int IInt;
	IInt i = 100;
	psln(i);
	typedef int IInt;
	IInt ii = 10000;
	psln(ii);
END_TEST
=======
typedef int IInt;
IInt i = 100;
psln(i);
typedef int IInt;
IInt ii = 10000;
psln(ii);
END_TEST;
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340

NS_END(c_lib_test);
NS_END(elloop);
