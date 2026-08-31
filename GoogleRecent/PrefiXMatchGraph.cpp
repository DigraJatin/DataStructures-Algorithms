class Solution {
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<int> ans;
    string labels, word;
};

void dfs(int node, int idx){
	ans[idx]++;

	// reached end of word
	if(idx == word.size()-1){
		return;
	}

	visited[node] = true;
	
	for(int nei : adj[node]){
		if(visited[nei]) continue;
		if(labels[nei] == word[idx + 1]){
			dfs(nei, idx + 1);
		}
	}

	visited[node] = false;
}

vector<int> countPaths(strin labels, vector<vector<int>>& edge, string word){
	int n = labels.size();
	// label = abclahs
	// node i has char label[i]
    this->labels = labels;
    this->word = word;
    adj.assign(n, {});
    visited.assign(n, false);
	ans.assign(word.size(), 0);

	for (auto& e : edges) {
        int u = e[0], v = e[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Every matching node can be the start of a path
    for (int i = 0; i < n; i++) {
        if (labels[i] == word[0]) {
            dfs(i, 0); // i is the node from where you are starting dfs
        }
    }

	return ans;
}

