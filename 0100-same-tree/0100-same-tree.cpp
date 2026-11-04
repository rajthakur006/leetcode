class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {

        // Both trees are empty
        if (p == NULL && q == NULL)
            return true;

        // One is empty, other is not
        if (p == NULL || q == NULL)
            return false;

        // Check current node values
        if (p->val != q->val)
            return false;

        // Check left and right subtrees
        return isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
};