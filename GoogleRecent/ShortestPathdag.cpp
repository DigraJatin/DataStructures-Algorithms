// dag with -ve wts, standard is bellmand ford but topo sort + edge relaxation can do better


int solve(int n, vector<vector<pair<int,int>>& graph, int src, int dest) {
	// topo sort
    vector<int> indegree(n);
    for (int u = 0; u < n; u++) {
        for (auto [v, weight] : graph[u]) {
            indegree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        topo.push_back(u);

        for (auto [v, weight] : graph[u]) {
            if (--indegree[v] == 0)
                q.push(v);
        }
    }

    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(n, INF);

    dist[src] = 0;

    for (int u : topo) {
        if (dist[u] == INF)
            continue;

        for (auto [v, weight] : graph[u]) {
            dist[v] = min(
                dist[v],
                dist[u] + weight
            );
        }
    }

    return dist[dst] == INF ? -1 : dist[dst];
}

// TC = O(V + E)
// SC = O(V)