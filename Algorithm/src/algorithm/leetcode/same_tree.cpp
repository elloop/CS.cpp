/**
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p) {
            return (q == nullptr);
        }

        if (!q) {
            return (p == nullptr);
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

