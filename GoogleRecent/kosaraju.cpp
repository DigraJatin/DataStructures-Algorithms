#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void dfs1(int node,
              vector<vector<int>>& adj,
              vector<int>& vis,
              stack<int>& st) {

        vis[node] = 1;

        for (int nei : adj[node]) {
            if (!vis[nei])
                dfs1(nei, adj, vis, st);
        }

        st.push(node);
    }

    void dfs2(int node,
              vector<vector<int>>& rev,
              vector<int>& vis,
              vector<int>& component) {

        vis[node] = 1;
        component.push_back(node);

        for (int nei : rev[node]) {
            if (!vis[nei])
                dfs2(nei, rev, vis, component);
        }
    }

    vector<vector<int>> kosaraju(int n,
                                 vector<vector<int>>& adj) {

        stack<int> st;
        vector<int> vis(n, 0);

        // Step 1: Finish order
        for (int i = 0; i < n; i++) {
            if (!vis[i])
                dfs1(i, adj, vis, st);
        }

        // Step 2: Reverse graph
        vector<vector<int>> rev(n);

        for (int u = 0; u < n; u++) {
            for (int v : adj[u]) {
                rev[v].push_back(u);
            }
        }

        // Step 3: DFS on reversed graph
        fill(vis.begin(), vis.end(), 0);

        vector<vector<int>> sccs;

        while (!st.empty()) {

            int node = st.top();
            st.pop();

            if (vis[node])
                continue;

            vector<int> component;
            dfs2(node, rev, vis, component);

            sccs.push_back(component);
        }

        return sccs;
    }
};

int main() {

    int n = 5;

    vector<vector<int>> adj(n);

    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    adj[2].push_back(3);
    adj[3].push_back(4);
    adj[4].push_back(3);

    Solution sol;

    auto sccs = sol.kosaraju(n, adj);

    for (auto &comp : sccs) {
        for (int node : comp)
            cout << node << " ";
        cout << "\n";
    }

    return 0;
}