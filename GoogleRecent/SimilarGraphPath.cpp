// Google On-site — Smallest Edit Distance to Convert Path
// Problem Statement

// You are given:

// A target path represented by strings:

// target = ["abc", "de", "xyz"]

// An undirected graph, where every node is also represented by a string.

// For example:

// ["ab", "x"]
// ["abc", "d"]
// ["de", "xyz"]
// ["pqr", "de"]
// ["d", "xy"]

// Each pair [u, v] represents an edge between nodes u and v.

// You need to construct another valid path in the graph having the same number of nodes as the target path.

// At position i, you choose some graph node v.

// The cost of choosing v at position i is the Levenshtein edit distance between:

// target[i] → v

// Allowed operations:

// Insert a character
// Delete a character
// Replace a character

// Each operation costs 1.

// Return the minimum total edit distance needed to convert the target path into a valid graph path.

// Recurisve thought

// solve(u, i)
// =
// editDistance(target[i], u)
// +
// min(
//     solve(v1, i+1),
//     solve(v2, i+1),
//     ...
// )

class Solution {
private:
    vector<vector<int>> adj;
    vector<string> nodes;
    vector<string> target;

    // memo[curr][index]
    // = minimum cost + corresponding path
    vector<vector<pair<int, vector<string>>>> memo;

    int editDist(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();

        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));

        for (int i = 0; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {

                if (i == 0) {
                    dp[i][j] = j;
                }
                else if (j == 0) {
                    dp[i][j] = i;
                }
                else if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = 1 + min({
                        dp[i - 1][j],     // delete
                        dp[i][j - 1],     // insert
                        dp[i - 1][j - 1]  // replace
                    });
                }
            }
        }

        return dp[n1][n2];
    }

    pair<int, vector<string>> solve(int curr, int index) {

        // Already computed
        if (memo[curr][index].first != -1) {
            return memo[curr][index];
        }

        int cost = editDist(target[index], nodes[curr]);

        // Last position
        if (index == target.size() - 1) {
            return memo[curr][index] = {
                cost,
                {nodes[curr]}
            };
        }

        pair<int, vector<string>> best{INT_MAX, {}};

        // Try every possible next node
        for (int next : adj[curr]) {

            auto sub = solve(next, index + 1);

            if (cost + sub.first < best.first) {

                best.first = cost + sub.first;

                best.second = sub.second;

                // Add current node to front
                best.second.insert(
                    best.second.begin(),
                    nodes[curr]
                );
            }
        }

        return memo[curr][index] = best;
    }

public:
    pair<int, vector<string>> minimumEditDistance(
        int n,
        vector<string>& inputNodes,
        vector<string>& inputTarget,
        vector<vector<string>>& edges
    ) {
        nodes = inputNodes;
        target = inputTarget;

        unordered_map<string, int> id;

        for (int i = 0; i < n; i++) {
            id[nodes[i]] = i;
        }

        adj.assign(n, {});

        for (auto& e : edges) {
            int u = id[e[0]];
            int v = id[e[1]];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // -1 means "not computed"
        memo.assign(
            n,
            vector<pair<int, vector<string>>>(
                target.size(),
                {-1, {}}
            )
        );

        pair<int, vector<string>> res{INT_MAX, {}};

        // Any node can be the starting node
        for (int i = 0; i < n; i++) {
            auto sub = solve(i, 0);

            if (sub.first < res.first) {
                res = sub;
            }
        }

        return res;
    }
};


// optimized

class Solution {
private:
    vector<vector<int>> adj;
    vector<string> nodes;
    vector<string> target;

    // memo[curr][index] = minimum cost from this state onward
    vector<vector<int>> memo;

    // nextNode[curr][index] = best next node to take
    vector<vector<int>> nextNode;

    int editDist(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();

        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));

        for (int i = 0; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {

                if (i == 0) {
                    dp[i][j] = j;
                }
                else if (j == 0) {
                    dp[i][j] = i;
                }
                else if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = 1 + min({
                        dp[i - 1][j],     // delete
                        dp[i][j - 1],     // insert
                        dp[i - 1][j - 1]  // replace
                    });
                }
            }
        }

        return dp[n1][n2];
    }

    int solve(int curr, int index) {

        // Already computed
        if (memo[curr][index] != -1) {
            return memo[curr][index];
        }

        int cost = editDist(target[index], nodes[curr]);

        // Last position
        if (index == target.size() - 1) {
            return memo[curr][index] = cost;
        }

        int best = INT_MAX;

        // Try every possible next node
        for (int next : adj[curr]) {

            int sub = solve(next, index + 1);

            if (cost + sub < best) {
                best = cost + sub;

                // Remember which next node gave us the best answer
                nextNode[curr][index] = next;
            }
        }

        return memo[curr][index] = best;
    }

public:
    pair<int, vector<string>> minimumEditDistance(
        int n,
        vector<string>& inputNodes,
        vector<string>& inputTarget,
        vector<vector<string>>& edges
    ) {
        nodes = inputNodes;
        target = inputTarget;

        // String -> integer ID
        unordered_map<string, int> id;

        for (int i = 0; i < n; i++) {
            id[nodes[i]] = i;
        }

        // Build graph
        adj.assign(n, {});

        for (auto& e : edges) {
            int u = id[e[0]];
            int v = id[e[1]];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int m = target.size();

        // Initialize DP
        memo.assign(n, vector<int>(m, -1));
        nextNode.assign(n, vector<int>(m, -1));

        // Try every node as starting node
        int bestCost = INT_MAX;
        int bestStart = -1;

        for (int start = 0; start < n; start++) {

            int cost = solve(start, 0);

            if (cost < bestCost) {
                bestCost = cost;
                bestStart = start;
            }
        }

        // Reconstruct path
        vector<string> path;

        int curr = bestStart;

        for (int index = 0; index < m; index++) {

            path.push_back(nodes[curr]);

            if (index == m - 1)
                break;

            curr = nextNode[curr][index];
        }

        return {bestCost, path};
    }
};