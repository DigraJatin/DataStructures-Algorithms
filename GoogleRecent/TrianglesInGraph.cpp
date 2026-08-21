#include <bits/stdc++.h>
using namespace std;


// ============================================================
// 1. TRIANGLE EXISTS
// ============================================================
//
// Brute force:
// - Pick 3 vertices (u, v, w)
// - Check whether (u,v), (v,w), (u,w) all exist
// - TC: O(N^3)
// - Requires hashset for O(1) average edge lookup
//
// Optimal:
// - Iterate over every edge (u,v)
// - Find a common direct neighbor w
// - Use hashset for O(1) average lookup
//
// TC:
// Build graph: O(N + E)
// Triangle check: O(Σ min(deg(u), deg(v))) = O(E√E)
// Overall: O(N + E√E)
//
// SC:
// Neighbor hash sets: O(N + E)
//

bool hasTriangle(vector<vector<int>>& edges, int N) {
    vector<unordered_set<int>> neighbours(N);

    // Build graph: O(N + E)
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];

        neighbours[u].insert(v);
        neighbours[v].insert(u);
    }

    // For every edge (u,v), find common neighbor w
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];

        // Iterate over smaller-degree node
        if (neighbours[u].size() > neighbours[v].size()) {
            swap(u, v);
        }

        for (int w : neighbours[u]) {
            // w is connected to both u and v
            if (neighbours[v].count(w)) {
                return true;
            }
        }
    }

    return false;
}


// ============================================================
// 2. COUNT TRIANGLES - BRUTE FORCE
// ============================================================
//
// Pick every 3 vertices.
//
// u < v < w guarantees that every triangle is counted once.
//
// TC:
// Build graph: O(N + E)
// Pick 3 vertices: O(N^3)
// Edge checks: O(1) average using hashset
// Overall: O(N^3)
//
// SC:
// Neighbor hash sets: O(N + E)
//

long long countTrianglesBrute(vector<vector<int>>& edges, int N) {
    vector<unordered_set<int>> neighbours(N);

    // Build graph: O(N + E)
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];

        neighbours[u].insert(v);
        neighbours[v].insert(u);
    }

    long long count = 0;

    // Pick every 3 vertices
    for (int u = 0; u < N; u++) {
        for (int v = u + 1; v < N; v++) {
            for (int w = v + 1; w < N; w++) {

                // Check (u,v), (v,w), (u,w)
                if (neighbours[u].count(v) &&
                    neighbours[v].count(w) &&
                    neighbours[u].count(w)) {
                    count++;
                }
            }
        }
    }

    return count;
}


// ============================================================
// 3. COUNT TRIANGLES - OPTIMAL
// ============================================================
//
// For every edge (u,v):
// - Find all common neighbors w
// - Every common neighbor forms one triangle
//
// Each triangle is encountered through each of its 3 edges:
//
//      u
//     / \
//    w---v
//
// (u,v), (u,w), (v,w)
//
// Therefore divide the final count by 3.
//
// TC:
// Build graph: O(N + E)
// Triangle counting:
// O(Σ min(deg(u), deg(v))) = O(E√E)
// Overall: O(N + E√E)
//
// SC:
// Neighbor hash sets: O(N + E)
//

long long countTriangles(vector<vector<int>>& edges, int N) {
    vector<unordered_set<int>> neighbours(N);

    // Build graph: O(N + E)
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];

        neighbours[u].insert(v);
        neighbours[v].insert(u);
    }

    long long count = 0;

    // For every edge (u,v), count common neighbors
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];

        // Iterate over smaller-degree node
        if (neighbours[u].size() > neighbours[v].size()) {
            swap(u, v);
        }

        for (int w : neighbours[u]) {
            if (neighbours[v].count(w)) {
                count++;
            }
        }
    }

    // Every triangle was counted once for each of its 3 edges
    return count / 3;
}


// ============================================================
// 4. COUNT QUADRILATERALS
// ============================================================
//
// A quadrilateral (cycle of length 4) exists if some pair
// of vertices has at least 2 common neighbors.
//
// Example:
//
//       a
//      / \
//     u   v
//      \ /
//       b
//
// u and v have common neighbors {a,b}.
//
// If a pair has k common neighbors:
//
// Number of quadrilaterals = C(k,2)
//                            = k * (k - 1) / 2
//
// Every quadrilateral is counted twice:
// - once using one pair of opposite vertices
// - once using the other pair of opposite vertices
//
// Therefore divide the final count by 2.
//
// TC:
// Build graph: O(N + E)
// Check all vertex pairs: O(N^3) worst case
// Overall: O(N^3)
//
// More precisely, common-neighbor work is:
// O(Σ over pairs min(deg(u), deg(v)))
//
// But worst case this is O(N^3).
//
// SC:
// Neighbor hash sets: O(N + E)
//

long long countQuadrilaterals(vector<vector<int>>& edges, int N) {
    vector<unordered_set<int>> neighbours(N + 1);

    // Build graph: O(N + E)
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];

        neighbours[u].insert(v);
        neighbours[v].insert(u);
    }

    long long count = 0;

    // Pick every pair of vertices
    for (int u = 1; u <= N; u++) {
        for (int v = u + 1; v <= N; v++) {

            int a = u;
            int b = v;

            // Iterate over smaller-degree node
            if (neighbours[a].size() > neighbours[b].size()) {
                swap(a, b);
            }

            int common = 0;

            // Find common neighbors of a and b
            for (int w : neighbours[a]) {
                if (neighbours[b].count(w)) {
                    common++;
                }
            }

            // Choose any 2 common neighbors
            count += 1LL * common * (common - 1) / 2;
        }
    }

    // Every quadrilateral counted twice
    return count / 2;
}

// Triangle existence
//     ↓
// edge (u,v) + ≥1 common neighbor


// Triangle counting
//     ↓
// edge (u,v) + count common neighbors
//     ↓
// divide by 3


// Quadrilateral existence
//     ↓
// pair (u,v) + ≥2 common neighbors


// Quadrilateral counting
//     ↓
// pair (u,v) + C(common, 2)
//     ↓
// divide by 2

// https://leetcode.com/submissions/detail/2108253999/
// https://leetcode.com/problems/shortest-cycle-in-a-graph/submissions/2108274043/


// Cycle of length N in a graph with N vertices → Hamiltonian Cycle.

// backtracking O(N!) 
class Hamiltonian{
public :
    int n;
    vector<vector<int>> graph;
    vector<int> path;
    vector<bool> visited;

    // u is the node we are standing at currently or reached
    bool dfs(int u){
        if(path.size() == n) return graph[u][path[0]];

        for(int v = 0; v < n; v++){
            if(!visited[v] && graph[u][v]){
                visited[v] = true;
                path.push_back(v);

                if(dfs(v)) return true;

                path.pop_back();
                visited[v] = false;
            }
        }
    }
    
    // adj matrix is given as input
    bool hasHamiltonianCycle(vector<vector<int>>& adj){
        graph = adj;
        n = graph.size();
        visited.assign(n, false);

        visited[0] = true;
        path.push_back(0);
        return dfs(0);
    }        
};

// Bitmask DP to bring down TC from O(N!) to O(2^N * N^2).
//
// Represent the set of visited vertices using a bitmask.
// Example:
// visited = {0, 2, 4}
// mask = 10101
//
// The ith bit is set if vertex i has been visited.
//
// DP state:
// dp[mask][u] = can we start at vertex 0,
//               visit exactly the vertices in 'mask',
//               and end at vertex 'u'?
//
// Since we fix vertex 0 as the starting vertex, the initial state is:
// dp[000...001][0] = true.
//
// At the end, we need to visit every vertex and then return to 0.
// Therefore, we need:
//
// dp[fullMask][u] == true AND graph[u][0] == true
//
// for some u != 0.
//
// We do NOT look for dp[fullMask][0], because that would mean
// returning to vertex 0 inside the DP, causing vertex 0 to be visited twice.
// O(N!)→O(2^N.N^2)

class Solution {
public:
    int n;
    int fullMask;

    vector<vector<int>> graph;
    vector<vector<int>> dp;

    bool solve(int mask, int u) {

        // All vertices have been visited.
        // We are currently at u.
        //
        // Check whether we can close the cycle by going back to 0.
        if (mask == fullMask)
            return graph[u][0];

        // Already computed.
        if (dp[mask][u] != -1)
            return dp[mask][u];

        // Try every unvisited vertex as the next vertex.
        for (int v = 0; v < n; v++) {

            // v is unvisited AND there is an edge u -> v.
            if ((mask & (1 << v)) == 0 && graph[u][v]) {

                // Mark v as visited and continue from v.
                if (solve(mask | (1 << v), v))
                    return dp[mask][u] = 1;
            }
        }

        // No unvisited neighbor leads to a Hamiltonian cycle.
        return dp[mask][u] = 0;
    }

    bool hasHamiltonianCycle(vector<vector<int>>& adj) {
        graph = adj;
        n = graph.size();

        // Mask with all n bits set.
        // Example: n = 4 -> 1111 -> 15.
        fullMask = (1 << n) - 1;

        // -1 = not computed
        //  0 = impossible
        //  1 = possible
        dp.assign(1 << n, vector<int>(n, -1));

        // Start at vertex 0.
        // Only vertex 0 has been visited initially.
        // Binary mask: 000...001
        return solve(1, 0);
    }
};