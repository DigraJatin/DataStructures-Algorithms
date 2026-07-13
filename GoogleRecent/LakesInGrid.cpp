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