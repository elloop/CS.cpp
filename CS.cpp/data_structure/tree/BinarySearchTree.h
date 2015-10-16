#pragma once
#include "inc.h"

NS_BEGIN(elloop);
template <typename T>
class BST {
public:
    BST() { psln(__FUNCTION__); }
};

template <typename T>
using BinarySearchTree = BST<T>;

// TODO: must i use using grammar to define type BinarySearchTree<T>?
//template <typename T>
//typedef BST<T> BinarySearchTree<T>;

NS_END(elloop);