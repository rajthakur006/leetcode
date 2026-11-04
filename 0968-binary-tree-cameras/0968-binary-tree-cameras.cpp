class Solution {
public:
    int cameras = 0;

    // 0 = Not covered
    // 1 = Has camera
    // 2 = Covered

    int dfs(TreeNode* root) {

        if (root == NULL)
            return 2;

        int left = dfs(root->left);
        int right = dfs(root->right);

        // If any child is not covered
        if (left == 0 || right == 0) {
            cameras++;
            return 1;
        }

        // If any child has a camera
        if (left == 1 || right == 1) {
            return 2;
        }

        // Both children are covered
        return 0;
    }

    int minCameraCover(TreeNode* root) {

        if (dfs(root) == 0) {
            cameras++;
        }

        return cameras;
    }
};