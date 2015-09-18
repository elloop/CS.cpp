#include "pod_test.h"

NS_ELLOOP_BEGIN

PodTest* PodTest::run() {
  psln(std::is_trivial<PodTest>::value);
  psln(std::is_trivial<t1>::value);
  psln(std::is_trivial<t2>::value);
  psln(std::is_trivial<nt1>::value);
  psln(std::is_trivial<nt2>::value);
  return this;
}



NS_ELLOOP_END
