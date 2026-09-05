// Initial Question: You are given an n×m grid and start from the bottom-left corner with the goal of reaching the bottom-right corner. 
//The allowed moves are only to the right, diagonally up-right, and diagonally down-right. 
//The task is to determine the total number of unique paths that can lead you from the starting point to the destination while adhering to these movement rules.

// Follow-Up 1: A list of specific checkpoints within the grid is now introduced. In this variation, 
// you are required to count only those paths that pass through each of these checkpoints once before reaching the bottom-right corner.

// Follow-Up 2: The order of visiting these checkpoints is now specified. 
// For example, if the checkpoints are labeled 1, 2, and 3, any valid path must encounter checkpoint 1 first, then checkpoint 2, and finally checkpoint 3, 
// in that exact sequence, on its way to the destination.

// https://leetcode.com/discuss/post/6038441/google-l4-phonescreen-by-anonymous_user-zqpk/

// initial question
// naive solution is 2d dp but optimized is 1d dp storing both first row and virst col

// dp[i][j]=dp[i][j−1]+dp[i−1][j−1]+dp[i+1][j−1]
// i-1, j-1
// i, j-1    ---> i,j
// i+1, j-1

// we can store the entire prev col

vector<int> prevCol(m, 0), dp(m);
prevCol[m-1] = 1;

for(int j = 1; j < n; j++) {
	for(int i = m-1; i >= 0; i--){
		dp[i] = prevCol[i]; // right movement
		// add other movements if valid
		if(i + 1 < m){
			dp[i] += prevCol[i+1];
		}

		if(i-1 >= 0){
			dp[i] += prevCol[i-1];
		}
	}
	prevCol = dp;
}

return dp[m-1];

// follow up 1
// each col has 1 checkpoint only other wise non reachable
// col 0 has checkpoint at start bottom left, col n-1 has at bottom right end point
// C0 -> C1 -> C2 -> C3 , every move increase coloumn poistion by 1, row pos can stay same +1, or -1
// but this condition enforces only 1 path possible such way

int countPaths(vector<pair<int,int>>& checkpoints) {

    for (int i = 1; i < checkpoints.size(); i++) {
        int prevRow = checkpoints[i - 1].first;
        int currRow = checkpoints[i].first;

        if (abs(currRow - prevRow) > 1)
            return 0; // not possible
    }

    return 1;
}

// If follow up one means not every col has checkpoint, just some random distributed in grid
// then 

   //               Original Problem
   //                     ↓
   //            ways(A, B)
   //                     ↓
   //      ┌──────────────┴──────────────┐
   //      ↓              ↓              ↓
   // Start → C1      C1 → C2        C2 → End
   //      ↓              ↓              ↓
   //     DP             DP             DP
   //      └──────────────┬──────────────┘
   //                     ↓
   //                  multiply

// just reuse the same initial problem solution calling it on start, C1....C1,C2.....C2,end
// multiply all the ways
// follow up 2 is redundant