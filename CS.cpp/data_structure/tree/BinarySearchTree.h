#pragma once
#include "inc.h"

NS_BEGIN(elloop);
template <typename Comparable>
class BST {
public:
    BST() : root_(nullptr) { psln(__FUNCTION__); }
    ~BST() {
        clear();
    }
    void insert(const Comparable & value) {
        insert(root_, value);
    }
    void printTree() const {
        printTree(root_, 1);
    }
    void clear() {
        clear(root_);
    }
    bool empty() const {
        return (root_ == nullptr);
    }
private:
    struct BSTNode {
        BSTNode(const Comparable& argData, BSTNode* argLeft = nullptr, 
                BSTNode* argRight = nullptr) 
            : data(argData),left(argLeft),right(argRight)
        { 

        }
        Comparable      data;
        BSTNode         *left;
        BSTNode         *right;
    };
    BSTNode             *root_;
    void insert(BSTNode* & tree, const Comparable& value) {
        if (!tree) {
            tree = new BSTNode(value, nullptr, nullptr);
        }
        else if (value < tree->data) {
            insert(tree->left, value);
        }
        else if (value > tree->data) {
            insert(tree->right, value);
        }
    }
     void printTree(const BSTNode* tree, size_t indent) const {
         if (tree) {
             printTree(tree->right, indent + 4);
             for (size_t i=0; i<indent; ++i) {
                 p(' ');
             }
             pln(tree->data);
             printTree(tree->left, indent + 4);
         }
     }
     void clear(BSTNode* & tree) {
         if (tree) {
             clear(tree->left);
             clear(tree->right);
             EL_SAFE_DELETE(tree);
         }
     }
};

template <typename T>
using BinarySearchTree = BST<T>;

// TODO: must i use using grammar to define type BinarySearchTree<T>?
//template <typename T>
//typedef BST<T> BinarySearchTree<T>;

NS_END(elloop);