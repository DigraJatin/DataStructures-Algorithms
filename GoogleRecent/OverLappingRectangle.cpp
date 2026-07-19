/* Give n X n matrix and rectangles (r1, c1, r2, c2) every cell covered by a rectangle is +1
return final grid after all rectangles are drawn */
// Note cell positions are given, not cordinates

#include <iostream>
#include <vector>

using namespace std;

class Solution {
	public : 
		vector<vector<int>> getOverlappingGrid(int N, vector<vector<int>>& rectangles){
			vector<vector<int>> grid(N, vector<int>(N, 0));
			// grid is our diff array here
			for(auto rect : rectangles){
				int r1 = rect[0], c1 = rect[1], r2 = rect[2], c2 = rect[3];
				grid[r1][c1] ++;
				if(c2 + 1 < N) grid[r1][c2 + 1] --;
				if(r2 + 1 < N) grid[r2 + 1][c1] --;
				if(c2 + 1 < N && r2 + 1 < N) grid[r2 + 1][c2 + 1] ++;
			}

			for(int i = 0; i < N; i++){
				for(int j = 0; j < N; j++){
					int left = i - 1 >= 0 ? grid[i-1][j] : 0;
					int top = j - 1 >= 0 ? grid[i][j-1] : 0;
					int topLeftDaig = (i - 1 >= 0 && j - 1 >= 0) ? grid[i-1][j-1] : 0;
					grid[i][j] = grid[i][j] + left + top - topLeftDaig;
				}
			}

			return grid;
		}
};

int main() {
	int N = 5;
	vector<vector<int>> rectangles = {
	    {1,1,3,3},
	    {2,2,4,4}
	};
	Solution obj;
	auto res = obj.getOverlappingGrid(N, rectangles);

	// res should be a N x N matrix in valid answer
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cout << res[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}

// difference array on 1d matris [l, r]
// diff[l] += 1
// diff[r] -= 1


// difference array on 2d matrix
// need to start at r1,c1 and stop horizontally at r1,c2
// need to start at r1,c1 and stop vertically at r2, c1
// cell r2 + 1, c2 + 1 gets stopped twice (handle that)

// 2d array prefix sum
// prefix[i][j] = grid[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]