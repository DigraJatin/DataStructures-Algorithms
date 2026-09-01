// In a directed graph, 
// find all nodes reachable from a source that are also part of a cycle.


// find reacable using simple dfs from src
// then run kosaraju to find sccs
// nodes part of scc and also reachable are answer
// scc contains a cyle if it has more than 2 nodes
// for single size components check if self edge exists or not

// assume adj list is available to it
vector<int> dfs(int src){
	reachable[src] = true;
	for(int nei : adj[src]){
		if(!reachable[nei]) dfs(nei);
	}
}

// assum it has visited, and adj list and order
void dfs1(int u){
	visited[u] = true;
	for(int v : adj[u]){
		if(!visited[v]) dfs(v);
	}
	order.push_back(u); // after finished processing the node
}

vector<int> dfs2(int u){
	visited[u] = true;
	component.push_back(u); // here we push into component on the go
	for(int v : rev[u]){
		if(!visited[v]) dfs(v);
	}
}

vector<int> solve(int n, vector<vector<int>>& edges, int source) {
    vector<vector<int>> adj(n), rev(n); // rev is for transpose

    for (auto& e : edges) {
        int u = e[0], v = e[1];
        adj[u].push_back(v);
        rev[v].push_back(u); // transpose
    }
    Complexity

For V vertices and E edges:

First DFS: O(V + E)
Transpose: O(V + E)
Second DFS: O(V + E)

Overall:

O(V + E)

    // find all reachable nodes
    vector<bool> reachable(n, false);
    reachable = dfs(source);

    // Start kosaraju
    // First dfs, get finishing order in stack or vector
    stack<int> order;
    vector<bool> visited(n, false);

    for(int i = 0; i < n; i++){
    	if(!visited[i]) dfs1(i);
    }

    // second dfs on transpose
    fill(visited.begin(), visited.end(), false);
    vector<int> ans;
    // but dfs2 is done in reverse orer popping from stack

    while(!st.empty()){
    	int u = st.top();
    	st.pop();
    	vector<int> component = dfs2(u);

    	if(component.size() > 1){
    		for(int node : component){
    			if(reachable[node]) ans.push_back(node);
    		}
    	} else {
    		int node = component[0];
    		if(reachable[node]){
    			for(int v : adj[node]){
    				if(v == node) ans.push_back(node);
    			}
    		}
    	}
    }

    return ans;
}

// Complexity

// For V vertices and E edges:

// First DFS: O(V + E)
// Transpose: O(V + E)
// Second DFS: O(V + E)

// Overall:

// O(V + E)