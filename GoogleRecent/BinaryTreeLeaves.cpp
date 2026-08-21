// print leaves of binary tree in order

vector<vector<int>> res;

vector<vector<int>> getLeaves(TreeNode *root){
	solve(root);
	return res;
}

int solve(TreeNode* root){
	if(!root) return -1;

	int left = solve(root->left);
	int right = solve(root->right);

	int curr = max(left, right) + 1;

	if(res.size() == curr){
		res.push_back({});
	}

	res[curr].push_back(root->val);
	return curr;
}