#include "BinarySearchTree.h"

NS_BEGIN(elloop);

//---------------------- begin of new test ----------------------
BEGIN_TEST(BinarySearchTree, Construct, @0);
    
    using std::cin;
    BinarySearchTree<int> bt;
    EXPECT_TRUE(bt.empty());
    int value(0);
    while (cin >> value) {
        bt.insert(value);
        EXPECT_FALSE(bt.empty());
        bt.printTree();
    }
    pcln("clear tree");
    bt.clear();
    bt.printTree();
    EXPECT_TRUE(bt.empty());


END_TEST;

RUN_GTEST(BinarySearchTree, Construct, @@);
psln(__func__);
BinarySearchTreeConstruct();

END_TEST;


NS_END(elloop);