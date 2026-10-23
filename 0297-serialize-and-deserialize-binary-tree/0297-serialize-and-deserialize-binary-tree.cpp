class Codec {
public:
    // Serialize tree into a string
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "N,";
        }

        return to_string(root->val) + "," +
               serialize(root->left) +
               serialize(root->right);
    }

    // Deserialize string back into a tree
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        return buildTree(ss);
    }

private:
    TreeNode* buildTree(stringstream& ss) {
        string val;
        getline(ss, val, ',');

        if (val == "N") {
            return nullptr;
        }

        TreeNode* root = new TreeNode(stoi(val));
        root->left = buildTree(ss);
        root->right = buildTree(ss);

        return root;
    }
};
