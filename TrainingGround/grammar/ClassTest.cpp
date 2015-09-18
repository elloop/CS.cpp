#include "ClassTest.h"
#include "gtest/gtest.h"

NS_BEGIN(elloop);
NS_BEGIN(class_test)

TEST(ClassTest, Const) {
    pcln("ClassTest ---> Const");

    // 下面的代码展示了，返回对象内部指针成员的危险性。

    A       a;
    int*    pa = a.a();
    EXPECT_EQ(*pa, 10);
    //delete a.a();     // crash！ because in ~A() will delete a_ again.

    // 即使是使用const类型的指针，也阻止不了对返回的指针进行delete操作
    int* const pca = a.a();
    //delete pca;       // crash!


}

NS_END(class_test)
NS_END(elloop);