#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
    pair<int, int> getNumberOfLakes(const vector<vector<int>>& grid) {
        int countLakes = 0;
        int countIslands = 0;

        m = grid.size();
        if (m == 0) return {0, 0};

        n = grid[0].size();

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Mark all boundary-connected components
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 || j == 0 || i == m - 1 || j == n - 1) {
                    if (!visited[i][j]) {
                        dfs(i, j, grid[i][j], grid, visited);
                    }
                }
            }
        }

        // Count remaining enclosed components
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j]) {
                    if (grid[i][j] == 0) {
                        countIslands++;
                        dfs(i, j, 0, grid, visited);
                    } else {
                        countLakes++;
                        dfs(i, j, 1, grid, visited);
                    }
                }
            }
        }

        return {countLakes, countIslands};
    }

private:
    int m = 0, n = 0;

    void dfs(int r, int c,
             int target,
             const vector<vector<int>>& grid,
             vector<vector<bool>>& visited) {

        if (r < 0 || c < 0 || r >= m || c >= n)
            return;

        if (visited[r][c] || grid[r][c] != target)
            return;

        visited[r][c] = true;

        dfs(r + 1, c, target, grid, visited);
        dfs(r - 1, c, target, grid, visited);
        dfs(r, c + 1, target, grid, visited);
        dfs(r, c - 1, target, grid, visited);
    }
};

int main() {

    // 0 = land
    // 1 = water

    vector<vector<int>> grid = {
        {0,0,0,0,0,0},
        {0,1,1,0,1,0},
        {0,1,0,0,1,0},
        {0,1,1,1,1,0},
        {0,0,0,0,0,0}
    };

    Solution obj;

    auto ans = obj.getNumberOfLakes(grid);

    cout << "Closed Lakes   : " << ans.first << '\n';
    cout << "Closed Islands : " << ans.second << '\n';

    return 0;
}

/*
=== Lakes in Grid ===
Grid encoding: 0 = land, 1 = water
Goal: Count enclosed (interior) water regions (lakes) and enclosed land regions (islands).
A region is "enclosed" if it has NO cell touching the boundary of the grid.

Approach: Two-pass DFS
Pass 1 - Boundary flood-fill:
  - For every unvisited cell on the 4 borders, run DFS marking its entire same-value
    connected component as visited. This eliminates all components that touch the boundary.

Pass 2 - Interior counting:
  - Scan all cells; any still-unvisited cell belongs to an enclosed region.
  - If it's water (1) -> lake count++
  - If it's land  (0) -> island count++
  - Run DFS to mark the whole enclosed component as visited so it's not double-counted.

TC: O(M * N)
  - Every cell is visited at most twice (once in pass 1 boundary check, once in pass 2 scan),
    and each DFS call processes each cell exactly once.
  - Total work across all DFS calls = O(M * N)

SC: O(M * N)
  - O(M * N) for the visited matrix
  - O(M * N) for the DFS call stack in the worst case (entire grid is one connected component,
    stack depth = M * N). For large grids, an iterative BFS/DFS would be safer to avoid
    stack overflow.
*/