#ifndef ALGORITHM_DATA_STRUCTURE_AVL_TREE_H
#define ALGORITHM_DATA_STRUCTURE_AVL_TREE_H

struct AvlNode;

typedef struct AvlNode* AvlTree;
typedef struct AvlNode {
    AvlTree left;
    AvlTree right;
    int data;
    int height;
} AvlNode;

int Height(AvlTree root);
AvlTree Insert(int value, AvlTree root);

#endif // end ALGORITHM_DATA_STRUCTURE_AVL_TREE_H
