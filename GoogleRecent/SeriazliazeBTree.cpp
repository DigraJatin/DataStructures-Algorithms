// You are given a binary tree where each node is:

// struct TreeNode {
//     string val;
//     TreeNode* left;
//     TreeNode* right;
// };

// Implement two APIs:

// string serialize(TreeNode* root);
// TreeNode* deserialize(string code);

// The string value can contain anything, including:

// "" — empty string
// "null" — literal string
// ","
// "#"
// "\n"
// spaces
// arbitrary Unicode characters

// N                  → null TreeNode*
// <number>:<value>   → actual node

class Codec {
public:
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "N";
        }

        string res = to_string(root->val.size());
        res += ":";
        res += root->val;

        res += serialize(root->left);
        res += serialize(root->right);

        return res;
    }

    TreeNode* deserialize(const string& str) {
        int i = 0;
        return deserializeHelper(str, i);
    }

    TreeNode* deserializeHelper(const string& str, int& idx) {
        // null node
        if (str[idx] == 'N') {
            idx++;
            return nullptr;
        }

        // read len
        int len = 0;

        while (str[idx] != ':') {
            len = len * 10 + (str[idx] - '0');
            idx++;
        }

        idx++; // skip :

        // Read exactly len characters
        string val = str.substr(idx, len);
        idx += len;

        TreeNode* node = new TreeNode(val);

        node->left = deserializeHelper(str, idx);
        node->right = deserializeHelper(str, idx);

        return node;
    }
};