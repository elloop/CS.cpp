#include "binary_tree.h"
#include <queue>
#include <memory>
#include "algorithm.h"
NS_BEGIN(elloop)

template <typename T>
typename TreeHelper<T>::Tree* TreeHelper<T>::createBinaryTreeUsingLevelOrder(ValueList items) {
    // init a queue.
    // while index < items.size, new a tree node. and enqueue it's left and right child.
    // while the queue is not empty, pop and create node with items[index]
    auto nodesCount = items.size();
    if (0 == nodesCount) {
        return nullptr;
    }

    // create a tree.
    auto tree = new Tree();
    auto node = &(tree->root_);
    std::queue<Node** > childQueue;
    childQueue.push(node);

    size_t index(0);
    while (index < nodesCount) {
        node = childQueue.front();
        (*node) = new Node(items[index++]);
        childQueue.push(&((*node)->left_));
        childQueue.push(&((*node)->right_));
        childQueue.pop();
    }

    return tree;
}

template <typename T>
typename TreeHelper<T>::Tree* TreeHelper<T>::createBinaryTreeUsingPreAndInOrder(
    ValueList preOrder, ValueList inOrder) {
    if (preOrder.empty() ||
        inOrder.empty() ||
        inOrder.size() != preOrder.size()) {
        return nullptr;
    }
    Tree * tree = new Tree();
    tree->setRoot(createBinaryTreeUsingPreAndInOrder(preOrder, 0, preOrder.size() - 1,
        inOrder, 0, inOrder.size() - 1));
    return tree;
}

template <typename T>
typename TreeHelper<T>::Node* TreeHelper<T>::createBinaryTreeUsingPreAndInOrder(
    ValueList preOrder, size_t indexPl, size_t indexPr,
    ValueList inOrder, size_t indexIl, size_t indexIr) {
    if (indexPr < indexPl) {
        return nullptr;
    }
    if (indexIr < indexIl) {
        return nullptr;
    }
    T value = preOrder[indexPl];
    Node* root = new Node(value);

    // 取出多少个元素用来构造子树：到中序序列里面去找根在第几个。
    size_t count(0);
    while ((indexIl + count <= indexIr) && (value != inOrder[indexIl + count])) {
        ++count;
    }
    // 用count个元素来构建左子树，剩下的去构建右子树.
    root->setLeft(createBinaryTreeUsingPreAndInOrder(preOrder, indexPl + 1, indexPl + count,
        inOrder, indexIl, indexIl + count - 1));
    root->setRight(createBinaryTreeUsingPreAndInOrder(preOrder, indexPl + count + 1, indexPr,
        inOrder, indexIl + count + 1, indexIr));
    return root;
}


template <typename T>
void TreeHelper<T>::printBinaryTree(const Node * root, size_t indent, size_t inc) {
    if (nullptr == root) {
        return;
    }
    printBinaryTree(root->right_, indent + inc, inc);
    for (size_t i = 0; i < indent; ++i) {
        p(" ");
    }
    pln(root->value_);
    printBinaryTree(root->left_, indent + inc, inc);
}

template <typename T>
void TreeHelper<T>::releaseBinaryTree(Tree* tree) {
    changeBinaryTree(tree, [](Node * & node) {
        delete node;
        node = nullptr;
    });
}

template <typename T>
void TreeHelper<T>::changeBinaryTree(Tree* tree, typename Tree::visitor visit) {
    tree->postOrder(visit);
}

template <typename T>
size_t TreeHelper<T>::getBinaryTreeLeafCount(const Tree* tree) {
    size_t leafCount(0);
    countBinaryTreeLeaf(tree->root(), leafCount);
    return leafCount;
}

template <typename T>
void TreeHelper<T>::countBinaryTreeLeaf(const Node* node, size_t & count) {
    if (node != nullptr) {
        if (node->left() == nullptr && node->right() == nullptr) {
            ++count;
            return;
        }
        countBinaryTreeLeaf(node->left(), count);
        countBinaryTreeLeaf(node->right(), count);
    }
}

template <typename T>
size_t TreeHelper<T>::getTreeHeight(const Node* node) {
    size_t lHeight(0);
    size_t rHeight(0);
    size_t height(0);

    if (nullptr == node) {
        height = 0;
    }
    else {
        lHeight = getTreeHeight(node->left());
        rHeight = getTreeHeight(node->right());
        height = max(lHeight, rHeight) + 1;
    }
    return height;
}

template <typename T>
typename TreeHelper<T>::Tree* TreeHelper<T>::copyTree(const Tree* tree) {
    if (tree != nullptr) {
        Tree* treeCopy = new Tree();
        treeCopy->root_ = copySubTree(tree->root());
        return treeCopy;
    }
    return nullptr;
}

template <typename T>
typename TreeHelper<T>::Node * TreeHelper<T>::copySubTree(const Node* node) {
    if (nullptr == node) {
        return nullptr;
    }

    Node* left = copySubTree(node->left());
    Node* right = copySubTree(node->right());
    return new Node(node->value(), left, right);
}

template <typename T>
void TreeHelper<T>::logTreeInfo(const Tree* tree) {
    LOGD("height: %d, leaf count: %d\n", getTreeHeight(tree->root()),
        getBinaryTreeLeafCount(tree));
}


//---------------------- begin of new test ----------------------
BEGIN_TEST(BinaryTreeTest, CreateTreeLevelOrder, @@);
return;
pcln("only a root node");
BinaryTree<int> tree(new BinaryTreeNode<int>(1000));
TreeHelper<int>::printBinaryTree(tree.root(), 0);
TreeHelper<int>::releaseBinaryTree(&tree);

pcln("bigger tree");
std::vector<int> nodesInLevelOrder{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
std::shared_ptr<BinaryTree<int>> pTree(TreeHelper<int>::createBinaryTreeUsingLevelOrder(nodesInLevelOrder));
//auto pTree = TreeHelper<int>::createBinaryTreeUsingLevelOrder(nodesInLevelOrder);
TreeHelper<int>::printBinaryTree(pTree->root(), 0);
cr;
// add 10 to every node's value
TreeHelper<int>::changeBinaryTree(pTree.get(), [](BinaryTreeNode<int>* & node) {
    node->setValue(node->value() + 10);
});
TreeHelper<int>::printBinaryTree(pTree->root(), 0);

psln(TreeHelper<int>::getBinaryTreeLeafCount(pTree.get()));
psln(TreeHelper<int>::getTreeHeight(pTree->root()));

// copy tree.
std::shared_ptr<BinaryTree<int>> copy(TreeHelper<int>::copyTree(pTree.get()));
EXPECT_TRUE(copy != nullptr);

TreeHelper<int>::releaseBinaryTree(pTree.get());

EXPECT_EQ(0, TreeHelper<int>::getBinaryTreeLeafCount(pTree.get()));
EXPECT_EQ(0, TreeHelper<int>::getTreeHeight(pTree->root()));
EXPECT_EQ(nullptr, pTree->root());

// shared_ptr auto delete.
//delete pTree; 
// pTree is dead.

// now the copy tree is still alive.
psln(TreeHelper<int>::getBinaryTreeLeafCount(copy.get()));
psln(TreeHelper<int>::getTreeHeight(copy->root()));
TreeHelper<int>::printBinaryTree(copy->root(), 0);
TreeHelper<int>::releaseBinaryTree(copy.get());
EXPECT_EQ(0, TreeHelper<int>::getBinaryTreeLeafCount(copy.get()));
EXPECT_EQ(0, TreeHelper<int>::getTreeHeight(copy->root()));
EXPECT_EQ(nullptr, copy->root());

//delete copy;

END_TEST;


//---------------------- begin of new test ----------------------
BEGIN_TEST(BinaryTreeTest, CreateTreePreInOrder, @@);

return;
std::vector<char> preOrder{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
std::vector<char> inOrder{ 'B', 'C', 'A', 'E', 'D', 'G', 'H', 'F', 'I' };

// create tree using preOrder and inOrder sequences.
BinaryTree<char> * tree = TreeHelper<char>::createBinaryTreeUsingPreAndInOrder(preOrder, inOrder);
pln("original input preOrder nodes:");
printArrayLikeContainer(preOrder);

auto printFunc = [](const BinaryTreeNode<char>* node) { p(node->value()); };

pln("use tree's preOrder iteration");
tree->preOrder(printFunc);
pln("\nand the non recursive version");
tree->preOrderNonRecursive(printFunc);
cr;

pln("original input inOrder nodes:");
printContainerNormally(inOrder);

pln("use tree's inOrder iteration");
tree->inOrder(printFunc);
pln("\nand the non recursive version");
tree->inOrderNonRecursive(printFunc);
cr;

pln("use tree's postOrder iteration");
tree->postOrder(printFunc);
cr;

pcln("Tree Construct Result:");
TreeHelper<char>::logTreeInfo(tree);
TreeHelper<char>::printBinaryTree(tree->root(), 0);
cr;

TreeHelper<char>::releaseBinaryTree(tree);
EXPECT_EQ(nullptr, tree->root());
EXPECT_EQ(0, TreeHelper<char>::getBinaryTreeLeafCount(tree));
EXPECT_EQ(0, TreeHelper<char>::getTreeHeight(tree->root()));
delete tree;

END_TEST;



NS_END(elloop)