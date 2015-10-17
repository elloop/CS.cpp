// memory leak check.
#ifdef _MSC_VER && _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// with detail description of memory leak.
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
void turnOnMemroyCheck() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
#endif

#include "include/inc.h"
#include "include/gtest/gtest.h"

void dummyExitFunction() {
	char c = getchar();
}
using namespace std;
#define TYPE_INFO(x) do { \
    std::cout << "type name of #x " << typeid(#x).name() << std::endl; \
    std::cout << "type name of aa " << typeid("aa").name() << std::endl; \
    std::cout << "type name of bb " << typeid("bb").name() << std::endl; \
    std::cout << "type name of aaa " << typeid("aaa").name() << std::endl; \
    std::cout << "type name of bbb " << typeid("bbb").name() << std::endl; \
    cout << "#x hash code: " << typeid(#x).hash_code() << endl; \
    cout << "aa hash code: " << typeid("aa").hash_code() << endl; \
    cout << "bb hash code: " << typeid("bb").hash_code() << endl; \
    cout << "aaa hash code: " << typeid("aaa").hash_code() << endl; \
    cout << "bbb hash code: " << typeid("bbb").hash_code() << endl; \
    const char * hello = "hello world"; \
    std::cout << "type name of const char* val " << typeid(hello).name() << std::endl; \
    std::cout << "type name of const char* type " << typeid(const char *).name() << std::endl; \
    cout << "const char* val hash code: " << typeid(hello).hash_code() << endl; \
    cout << "const char* type hash code: " << typeid(const char *).hash_code() << endl; \
    std::string str = #x; \
    cout << str << endl; \
    char h = #x[0]; \
    cout << h << endl; \
    } while (0);

int main(int argc, char** argv) {

#ifdef _MSC_VER && _DEBUG
	// make program stop when debug.
	atexit(dummyExitFunction);
	turnOnMemroyCheck();
#endif

    TYPE_INFO(hello);
	// use gtest.
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}