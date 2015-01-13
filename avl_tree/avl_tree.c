#include "avl_tree.h"
#include <stdlib.h>

void CreateAndInitTreeNode(AvlTree root, AvlTree leftChild, AvlTree rightChild, int data, int height)
{
    if (!root)
    {
        root = (AvlTree) malloc (sizeof (AvlNode));
    }
    root->left = leftChild;
    root->right = rightChild;
    root->data = data;
    root->height = height;
}

int Height(AvlTree root) {
    if (!root) {
        return -1;
    }
    return root->height;
}

AvlTree Insert(int value, AvlTree root) 
{
    if (!root)
    {

    }
    return root;
}
