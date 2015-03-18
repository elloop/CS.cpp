#include "compatibility.h"
#include "thread_test.h"
#include "constructor_test.h"
#include "pod_test.h"

USING_NS_ELLOOP;

#define TEST(x) do { delete (new (x))->run(); } while (0);
int main() {

  TEST(PodTest);

  // TEST(ConstructorTest);

  // TEST(ThreadTest);

  // TEST(Compatibility);

  return 0;
}
