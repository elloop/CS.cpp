_Pragma("once")
#include "inc.h"

NS_ELLOOP_BEGIN

class BaseTest {
  public:
    virtual ~BaseTest() {
      pcln("deleting a test.");
    }

    BaseTest() {
      pcln("creating a test.");
    }

    // BaseTest(int id) : id_(id) {
    //   pcln("creating a test.");
    // }

    virtual BaseTest * run() {};
  private:
    int id_;
};

NS_ELLOOP_END
