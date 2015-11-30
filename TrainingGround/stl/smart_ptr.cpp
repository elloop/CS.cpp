#include "smart_ptr.h"
#include "gtest/gtest.h"
#include "inc.h"
#include <memory>

NS_BEGIN(elloop);
NS_BEGIN(smart_ptr);

using namespace std;
<<<<<<< HEAD
BEGIN_TEST(SmartPointerTest, SharedPtrTest, @)
  pcln("SmartPointerTest --> SharedPtrTest");
  shared_ptr<Dog> pd(new Dog());
  psln(pd->age_);
END_TEST
=======
BEGIN_TEST(SmartPointerTest, SharedPtrTest, @);
pcln("SmartPointerTest --> SharedPtrTest");
shared_ptr<Dog> pd(new Dog());
psln(pd->age_);
END_TEST;
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340

NS_END(smart_ptr);
NS_END(elloop);