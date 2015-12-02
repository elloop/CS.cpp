#include "smart_ptr.h"
#include "gtest/gtest.h"
#include "inc.h"
#include <memory>

NS_BEGIN(elloop);
NS_BEGIN(smart_ptr);

using namespace std;

BEGIN_TEST(SmartPointerTest, SharedPtrTest, @);
pcln("SmartPointerTest --> SharedPtrTest");
shared_ptr<Dog> pd(new Dog());
psln(pd->age_);
END_TEST;

NS_END(smart_ptr);
NS_END(elloop);