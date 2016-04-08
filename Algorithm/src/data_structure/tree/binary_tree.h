#ifdef _MSC_VER
__pragma( "once" )
#else
_Pragma( "once" )
#endif

#include "inc.h"
#include <stack>

NS_BEGIN(elloop)

// operations T should support:
// 1. copy assignment =;
// 2.

template <typename T> class BinaryTree;
template <typename T> class TreeHelper;

template <typename T>
class BinaryTreeNode {
public:
  BinaryTreeNode(const T & value, 
                    BinaryTreeNode* left    = nullptr, 
                    BinaryTreeNode* right   = nullptr): 
    value_(value), 
    left_(left), 
    right_(right) 
  {}

  ~BinaryTreeNode() {
    p("deleting node, value:");
    pln(value_);
  }

  // getter and setter
  void setValue(T value) { value_ = value; }
  const T& value() const { return value_; }

  void setLeft(BinaryTreeNode* left) { left_ = left; }
  const BinaryTreeNode* left() const { return left_; }

  void setRight(BinaryTreeNode* right) { right_ = right; }
  const BinaryTreeNode* right() const { return right_; }

  friend BinaryTree<T>;
  friend TreeHelper<T>;
private:
  T                 value_;
  BinaryTreeNode*   left_;
  BinaryTreeNode*   right_;
};

template <typename T>
class BinaryTree {
public:
  typedef typename elloop::BinaryTreeNode<T> Node;
  typedef void(*const_visitor)( const BinaryTreeNode<T>* );
  typedef void(*visitor)( BinaryTreeNode<T>* & );

  BinaryTree(Node* root = nullptr) : 
      root_(root) 
  {}

  ~BinaryTree() {
    clear();
  }

  // basic operations.
  bool root(T& value) const {
    if ( nullptr == root_ ) {
      return false;
    }
    else {
      value = root_->value_;
      return true;
    }
  }

  void setRoot(Node* root) { root_ = root; }
  const Node* root() const { return root_; }
  Node*& mutableRoot() { return root_; }

  bool empty() const { return ( root_ == nullptr ); }

  // iteration. recursive.
  void preOrder(const_visitor visitFunc) { preOrder(visitFunc, root_); }
  void preOrder(visitor visitFunc) { preOrder(visitFunc, root_); }

  void inOrder(const_visitor visitFunc) { inOrder(visitFunc, root_); }
  void inOrder(visitor visitFunc) { inOrder(visitFunc, root_); }

  void postOrder(const_visitor visitFunc) { postOrder(visitFunc, root_); }
  void postOrder(visitor visitFunc) { postOrder(visitFunc, root_); }

  // iteration non-recursive.
  void preOrderNonRecursive(const_visitor visitFunc) {
    using std::stack;
    const Node* pointer = root_;
    stack<const Node*> pointerStack;

    while ( pointer != nullptr || !pointerStack.empty() ) {
      while ( pointer != nullptr ) {
        visitFunc(pointer);               // visit root of sub tree.
        pointerStack.push(pointer);   
        pointer = pointer->left();    // walk to leftmost.
      }
      if (!pointerStack.empty()) {
        pointer = pointerStack.top();
        pointerStack.pop();
        pointer = pointer->right();   // one step towards right.
      }
    }
  }

  void inOrderNonRecursive(const_visitor visitFunc) {
    using std::stack;
    const Node* pointer = root_;
    stack<const Node*> pointerStack;

    while ( pointer != nullptr || !pointerStack.empty() ) {
      while ( pointer != nullptr ) {
        pointerStack.push(pointer);
        pointer = pointer->left();    // walk to leftmost.
      }
      if ( !pointerStack.empty() ) {
        pointer = pointerStack.top();
        visitFunc(pointer);               // visit root of sub tree.
        pointerStack.pop();
        pointer = pointer->right();   // one step towards right.
      }
    }
  }

  void postOrderNonRecursive(const_visitor visitFunc) {

  }

  void clear() {}

  friend TreeHelper<T>;
private:
  Node* root_;

  // real iteration.
  void preOrder(const_visitor visitFunc, Node * root) {
    if ( root != nullptr ) {
      visitFunc(root);
      preOrder(visitFunc, root->left_);
      preOrder(visitFunc, root->right_);
    }
  }

  void preOrder(visitor visitFunc, Node * &root) {
    if ( root != nullptr ) {
      visitFunc(root);
      preOrder(visitFunc, root->left_);
      preOrder(visitFunc, root->right_);
    }
  }

  void inOrder(const_visitor visitFunc, Node * root) {
    if ( root != nullptr ) {
      inOrder(visitFunc, root->left_);
      visitFunc(root);
      inOrder(visitFunc, root->right_);
    }
  }

  void inOrder(visitor visitFunc, Node * &root) {
    if ( root != nullptr ) {
      inOrder(visitFunc, root->left_);
      visitFunc(root);
      inOrder(visitFunc, root->right_);
    }
  }

  void postOrder(const_visitor visitFunc, Node * root) {
    if ( root != nullptr ) {
      postOrder(visitFunc, root->left_);
      postOrder(visitFunc, root->right_);
      visitFunc(root);
    }
  }

  void postOrder(visitor visitFunc, Node * &root) {
    if ( root != nullptr ) {
      postOrder(visitFunc, root->left_);
      postOrder(visitFunc, root->right_);
      visitFunc(root);
    }
  }
};


// TODO: make TreeHelper a Singleton class.
template <typename T>
class TreeHelper {
public:
  typedef elloop::BinaryTree<T> Tree;
  typedef elloop::BinaryTreeNode<T> Node;
  typedef typename Tree::visitor visitor;
  typedef typename Tree::const_visitor const_visitor;
  typedef const std::vector<T>& ValueList;

  static Tree* createBinaryTreeUsingLevelOrder(ValueList items);
  static Tree* createBinaryTreeUsingPreAndInOrder(ValueList preOrder, ValueList inOrder);
  
  static Tree* copyTree(const Tree * root);

  static void printBinaryTree(const Node * root, size_t indent = 0, size_t inc = 3 );

  static void logTreeInfo(const Tree* tree);

  static void releaseBinaryTree(Tree* tree);

  static void changeBinaryTree(Tree* tree, visitor visit);

  static size_t getBinaryTreeLeafCount(const Tree* tree);
  static size_t getTreeHeight(const Node * node);
private:
  static void countBinaryTreeLeaf(const Node* node, size_t & count);
  static Node * copySubTree(const Node* node);
  static Node* createBinaryTreeUsingPreAndInOrder(ValueList preOrder, size_t indexPl,
    size_t indexPr, ValueList inOrder, size_t indexIl, size_t indexIr);
};



NS_END(elloop)
