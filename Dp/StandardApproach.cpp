#include <iostream>
#include <vector>
#include <climits>

using namespace std;

/* The genric DP approach is - 
1. Build a recursive solution
2. Memoize the recursive solution also called as top-down approach or doing memoization
3. Convert the memoized solution to iterative also called as tabulation
4. Reduce space complexity if possible
5. That's it!
*/

// this gives TLE because of overlapping subproblems
// Time Complexity: Exponential = O(n^sqrt(n))
// Space Complexity: O(n) for the recursion stack
int solveRecursive(int n) {
    if(n == 0) return 0;
    if(n < 0) return INT_MAX;

    int ans = INT_MAX;
    for (int i = 1; i * i <= n; i++) {
        int sub = solveRecursive(n - i * i);
        if (sub != INT_MAX) {
            ans = min(ans, 1 + sub);
        }
    }
    return ans;
}

// now let's memoize the above recursive solution
// Time Complexity: O(n * sqrt(n))
// Space Complexity: O(n) for the dp array + O(n) for the recursion stack
int solveMemoized(int n, vector<int> &dp) {
    if(n == 0) return 0;
    if(n < 0) return INT_MAX;

    if(dp[n] != -1) return dp[n];

    int ans = INT_MAX;
    for (int i = 1; i * i <= n; i++) {
        int sub = solveMemoized(n - i * i, dp);
        if (sub != INT_MAX) {
            ans = min(ans, 1 + sub);
        }
    }
    return dp[n] = ans;
}

// tabulation of the above code is done like
// Time Complexity: O(n * sqrt(n))
// Space Complexity: O(n) for the dp array
int solveTabulated(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            dp[i] = min(dp[i], 1 + dp[i - j * j]);
        }
    }
    return dp[n];
}

// improved space optimized version of the above code
// Time Complexity: O(n * sqrt(n))
// Space Complexity: O(1)
int solveSpaceOptimized(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            dp[i] = min(dp[i], 1 + dp[i - j * j]);
        }
    }
    return dp[n];
}

// follows leetcode problem Perfect Squares - https://leetcode.com/problems/perfect-squares/
int main() {
    int n = 12;
    // recursive approach
    cout << "Minimum number of perfect squares (Recursive): " << solveRecursive(n) << endl;
    // memoized approach
    vector<int> dp(n + 1, -1);
    cout << "Minimum number of perfect squares (Memoized): " << solveMemoized(n, dp) << endl;
    // tabulated approach
    cout << "Minimum number of perfect squares (Tabulated): " << solveTabulated(n) << endl;
    // space optimized approach
    cout << "Minimum number of perfect squares (Space Optimized): " << solveSpaceOptimized(n) << endl;
    
    return 0;
}
