#include "ClassTest.h"
#include "gtest/gtest.h"

NS_BEGIN(elloop);
NS_BEGIN(class_test)

BEGIN_TEST(ClassTest, Const, @)
    pcln("ClassTest ---> Const");

    // 下面的代码展示了，返回对象内部指针成员的危险性。

    A       a;
    int*    pa = a.a();
    EXPECT_EQ(*pa, 10);
    //delete a.a();     // crash！ because in ~A() will delete a_ again.

    // 即使是使用const类型的指针，也阻止不了对返回的指针进行delete操作
    int* const pca = a.a();
    //delete pca;       // crash!

END_TEST



int ImplicitContructable::s_constructCount_ = 0;
BEGIN_TEST(ClassTest, ImplicitConstructor, @@@) ;

int objCount = ImplicitContructable::s_constructCount_;
ImplicitContructable ic({1});       // this will call constructor twice. one is for {} temp obj. the other is copy construct.
int nowCount = ImplicitContructable::s_constructCount_;
EXPECT_EQ(nowCount, (objCount + 2));


END_TEST;

NS_END(class_test)
NS_END(elloop);