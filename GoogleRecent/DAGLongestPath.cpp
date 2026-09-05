// assume we already have
int n;
vector<vector<int>> adj(n + 1);
vector<int> topo; // get it use Kahn bfs techinuqe

// Given a DAG, for every node u, find the length of the longest path ending at u.
vector<int> dpEnd(n + 1, 1);
for (int u : topo) {
    for (int v : adj[u]) {
        dpEnd[v] = max(dpEnd[v], dpEnd[u] + 1);
    }
}
// find maxu dp[u] to get the longest path ending at u

// For every node, find the longest path starting from it.
vector<int> dpStart(n + 1, 1);
for (int i = topo.size() - 1; i >= 0; i--) {
    int u = topo[i];

    for (int v : adj[u]) {
        dpStart[u] = max(dpStart[u], dpStart[v] + 1);
    }
}

// Longest path PASSING THROUGH each node
vector<int> answer(n + 1);
for (int i = 1; i <= n; i++) {
    answer[i] = dpEnd[i] + dpStart[i] - 1;
}