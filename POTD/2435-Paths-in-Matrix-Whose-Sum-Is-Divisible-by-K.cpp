#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        const int MOD = 1e9 + 7;
        // dp[row][col][remainder] = holds value = no of ways to reach row,col with remainder value
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k,0)));
        dp[0][0][grid[0][0]%k] = 1;

        for(int i = 0 ; i < m ; i++) {
            for(int j = 0; j < n ; j++) {
                if(i==0 && j==0) continue;
                for(int r = 0 ; r < k ; r++) {
                    int curr = grid[i][j];
                    int remainder = (r + curr)%k;

                    if(i>0){
                        dp[i][j][remainder] = (dp[i][j][remainder] + dp[i-1][j][r]) % MOD;
                    }
                    if(j>0){
                        dp[i][j][remainder] = (dp[i][j][remainder] + dp[i][j-1][r]) % MOD;
                    }
                }
            }
        }
        return dp[m-1][n-1][0];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<vector<int>> grid = {{5,2,4},{3,0,5},{0,7,2}};
    int k = 3;
    int result = sol.numberOfPaths(grid, k);
    cout << result << "\n";

    return 0;
}
