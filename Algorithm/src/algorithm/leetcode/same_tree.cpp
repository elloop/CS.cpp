#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p) {
            return (q == NULL);
        }

        if (!q) {
            return (p == NULL);
        }

        bool isSameRoot = (p->val == q->val);
        if (!isSameRoot) {
            return false;
        }
        bool isLeftSame  = isSameTree(p->left, q->left);
        bool isRightSame = isSameTree(p->right, q->right);
        return (isLeftSame && isRightSame);
    }

    bool isSameTreeCaoBo(TreeNode* p, TreeNode* q) {
        if (!p) {
            return (!q);
        }

        if (!q) {
            return false;
        }

        return (p->val == q->val && isSameTreeCaoBo(p->left, p->left) && isSameTreeCaoBo(p->right, q->right));
    }
};

