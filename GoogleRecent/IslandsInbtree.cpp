// Standard question

#include <unordered_map>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

struct IslandResult {
    int totalIslands;
    // islandsByValue is an unordered map that groups the islands according to their node value.
    // node value → list of island numbers having that value
    std::unordered_map<int, std::vector<int>> islandsByValue;
};

class Solution {
private:
    int islandCount;
    std::unordered_map<int, std::vector<int>> islandsByValue;
    
    void dfs(TreeNode* node, int parentVal) {
        if (!node) {
            return;
        }
        
        // If current node value differs from parent, new island starts
        if (node->val != parentVal) {
            islandCount++;
            
            // Track island by its value
            if (islandsByValue.find(node->val) == islandsByValue.end()) {
                islandsByValue[node->val] = std::vector<int>();
            }
            islandsByValue[node->val].push_back(islandCount);
        }
        
        // Continue DFS with current node's value as parent value
        dfs(node->left, node->val);
        dfs(node->right, node->val);
    }
    
public:
    IslandResult countTreeIslands(TreeNode* root) {
        /**
         * Count islands in a binary tree using DFS.
         * An island is a connected group of nodes with the same value.
         */
        if (!root) {
            return {0, {}};
        }
        
        // Track total islands and islands grouped by value
        islandCount = 0;
        islandsByValue.clear();
        
        // Start DFS - root is always the first island
        islandCount = 1;
        islandsByValue[root->val] = std::vector<int>();
        islandsByValue[root->val].push_back(islandCount);
        
        // Traverse children
        dfs(root->left, root->val);
        dfs(root->right, root->val);
        
        return {islandCount, islandsByValue};
    }
};


// Google variation

// 0 - water, 1 - island
// return no of islands
// use dfs


int dsf(TreeNode* node, bool isParentOne){
    if(!node) return 0;

    int count = 0;
    if(node->val == 1 && !isParentOne){
        count = 1;
    }

    bool isCurrOne = node->val == 1;
    count += dfs(node->left, isCurrOne);
    count += dfs(node->right, isCurrOne)
    return count;
}

int countIslands(TreeNode* root){
    return dfs(root, false);
}


// sizes of all the islands present
int maxSizeIsland = 0;

// returns size of islannd rooted at node
int dfs(TreeNode* node, bool isParentOne, vector<int>& sizes){
    if(!node) return 0;

    bool isCurrOne = node->val == 1;

    if(isCurrOne && !isParentOne){
        int size = 1;
        size += dfs(node->left, true, sizes);
        size += dfs(node->right, true, sizes);
        maxSizeIsland = max(maxSizeIsland, size);
        sizes.push_back(size);
        return 0; // size is not returned to parent island contri because parent was 0
    } else if(isCurrOne && isParentOne){
        int size = 1;
        size += dfs(node->left, true, sizes);
        size += dfs(node->right, true, sizes);
        return size;
    }

    dfs(node->left, false, sizes);
    dfs(node->right, false, sizes);
    return 0;
}

vector<int> getIslandsSizes(TreeNode* root){
    vector<int> res;
    dfs(root, fase, res);
}