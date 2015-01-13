#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    AvlTree root = NULL;
    root = (AvlTree) malloc(sizeof (AvlNode));
    root->left = NULL;
    root->right = NULL;
    root->height = 100;
    root->data = 1000;
    int height = Height(root);
    printf("height of tree: %d\n", height);
    printf("data of tree: %d\n", root->data);
    return 0;
}
