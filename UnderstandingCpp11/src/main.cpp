// memory leak check.
#if defined(_MSC_VER) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// with detail description of memory leak.
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
void turnOnMemroyCheck() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
#endif

#include "compatibility.h"
#include "thread_test.h"
#include "constructor_test.h"
#include "pod_test.h"
#include "initializer_test.h"
#include "lambda_test.h"
#include "gtest/gtest.h"

USING_NS_ELLOOP;

#define ELLOOP_TEST(x) do { delete (new (x))->run(); } while (0);

void dummyExitFunction() {
	int i(0);
}

int main(int argc, char** argv) {

#if defined(_MSC_VER) && defined(_DEBUG)
	// make program stop when debug.
	atexit(dummyExitFunction);

	turnOnMemroyCheck();
#endif

    // use gtest.
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

	//ELLOOP_TEST(LambdaTest);

	//ELLOOP_TEST(PodTest);

	// InitializerTest it({1, 2, 3});

	// ELLOOP_TEST(InitializerTest);
	// ELLOOP_TEST(ConstructorTest);

	// ELLOOP_TEST(ThreadTest);

	// ELLOOP_TEST(Compatibility);

	//return 0;
}
