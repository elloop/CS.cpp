#ifndef ALGORITHM_DATA_STRUCTURE_TREE_BINARY_THREAD_TREE_H
#define ALGORITHM_DATA_STRUCTURE_TREE_BINARY_THREAD_TREE_H

enum class LinkTag
{
    Link = 0,
    Thread = 1,
};

template <typename T>
struct BinaryThreadTreeNode
{
    T                       _data;
    BinaryThreadTreeNode    *_lchild;
    BinaryThreadTreeNode    *_rchild;
    LinkTag                 _ltag;
    LinkTag                 _rtag;
};


template <typename T>
using BThreadTreeNode = BinaryThreadTreeNode<T>;

#endif