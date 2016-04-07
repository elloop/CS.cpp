#include "BinarySearchTree.h"

NS_BEGIN(elloop);

//---------------------- begin of new test ----------------------
BEGIN_TEST(BinarySearchTree, Construct, @0);
    
    using std::cin;
    using std::vector;
    typedef int ValueType;
    typedef vector<ValueType> Array;
    BinarySearchTree<ValueType> bt;
    EXPECT_TRUE(bt.empty());
    int     value(0);
    Array   ary;
    while (cin >> value) {
        ary.push_back(value);
        bt.insert(value);
        EXPECT_FALSE(bt.empty());
        bt.printTree();
    }
    for (auto v : ary) {
        EXPECT_TRUE(bt.contains(v));
    }

    pcln("clear tree");
    bt.clear();
    bt.printTree();
    EXPECT_TRUE(bt.empty());

END_TEST;


NS_END(elloop);