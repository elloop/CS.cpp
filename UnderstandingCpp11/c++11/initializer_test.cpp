#include "initializer_test.h"
#include "gtest/gtest.h"
#include <type_traits>

NS_ELLOOP_BEGIN
TEST(Initializer_List, InitTest) {
    USING_NS_STD;
    InitializerTest it1({});
    EXPECT_EQ(0, it1.data().size());

    

    initializer_list<int> il = { 1, 2, 3 };
    InitializerTest it2(il);
    EXPECT_EQ(3, it2.data().size());
    auto counter = 0;
    auto iter = il.begin();
    while (iter != il.end()) {
        EXPECT_EQ(*iter, it2.data()[counter++]);
        ++iter;
    }
}

TEST(Initializer_List, IndexOperator) {
    USING_NS_STD;
    initializer_list<int> il = { 1, 2, 3 };
    InitializerTest it(il);

    initializer_list<int> indexs = { 1, 2, 3, 4};
    it[indexs];
    EXPECT_EQ(4, it.indexes().size());

    auto counter = 0;
    auto iter = indexs.begin();
    while (iter != indexs.end()) {
        EXPECT_EQ(*iter, it.indexes()[counter++]);
        ++iter;
    }
}

TEST(Initializer_List, AssignmentOperator) {
    USING_NS_STD;
    InitializerTest it({ 1, 2, 3 });
    it[{1, 2, 3, 4}] = 10;
    EXPECT_EQ(4, it.size());
    auto len = it.size();
    while (len--) {
        EXPECT_EQ(10, it.data()[len]);
    }
}

void funcA(A a) {}
void funcB(B b) {}

TEST(TypeConvert, CustomConverter) {
    
    // ??: why? 
    //EXPECT_EQ(10, ConvertToInt());

    ConvertToInt cit;
    EXPECT_EQ(10, cit());

    //---------------------------  ---------------------------
    CanBeAB ca;
    CanBeAB cb;
    bool sameA1 = std::is_same<decltype(ca()), A>::value;
    bool sameA2 = std::is_same<decltype(ca.operator A()), A>::value;
    EXPECT_TRUE(sameA1);
    EXPECT_TRUE(sameA2);

    bool sameB1 = std::is_same<decltype(cb()), A>::value;
    bool sameB2 = std::is_same<decltype(cb.operator B), A>::value;
    EXPECT_TRUE(sameB1);
    EXPECT_FALSE(sameB2);

    void funcA(A a);
    void funcB(B b);

    funcA(ca);
    //funcB(cb);  // error: cannot convert cb to B. (explicit operator B()).
   
    A a1(ca);
    A a2 = ca;

    B b1(cb);
    //B b2 = cb;     // error: cannot convert cb to B. (explicit operator B()). 
    B b3 = static_cast<B>(cb);
}
NS_ELLOOP_END
