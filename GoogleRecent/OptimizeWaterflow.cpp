class Solution {
public:
    vector<int> parent, rankv;

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py)
            return false;

        if (rankv[px] < rankv[py])
            swap(px, py);

        parent[py] = px;

        if (rankv[px] == rankv[py])
            rankv[px]++;

        return true;
    }

    int minCostToSupplyWater(vector<int>& wells,
                             vector<vector<int>>& pipes) {
        
        int n = wells.size();

        // Edge = {cost, u, v}
        vector<tuple<int, int, int>> edges;

        // Virtual node 0 -> house i
        // means: build a well at house i
        for (int i = 1; i <= n; i++) {
            edges.push_back({wells[i - 1], 0, i});
        }

        // Normal pipe edges
        for (auto& pipe : pipes) {
            int u = pipe[0];
            int v = pipe[1];
            int cost = pipe[2];

            edges.push_back({cost, u, v});
        }

        // Kruskal
        sort(edges.begin(), edges.end());

        parent.resize(n + 1);
        rankv.assign(n + 1, 0);

        for (int i = 0; i <= n; i++)
            parent[i] = i;

        int ans = 0;
        int edgesUsed = 0;

        for (auto& [cost, u, v] : edges) {
            if (unite(u, v)) {
                ans += cost;
                edgesUsed++;

                // n+1 nodes => n edges in MST
                if (edgesUsed == n)
                    break;
            }
        }

        return ans;
    }
};