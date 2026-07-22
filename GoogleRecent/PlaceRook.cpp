// given a matrix with n x n size
// an api getRookCount(r1, c1, r2, c2) returns no of rooks in the rectangle formed
// n-1 rooks are already placed
// find place to place the final rook

#include <iostream>
#include <vector>
#include <pair>

using namespace std;

class ChessBoard {
	public :
		int getRookCount(r1, c1, r2, c2){
			// some code here
		}

	private :
		int N;
}

class Solution {
	public :
		pair<int,int> getNthRookPosition(int n){
			int low = 1, high = n;
			ChessBoard obj;

			while(low < high){
				int mid = low + (high-low)/2;
				int count = obj.getRookCount(1, 1, mid, n);

				if(count == (mid - low + 1)){
					// search half below mid
					low = mid + 1;
				} else {
					// search in same half
					hi = mid;
				}
			}

			int row = low;

			low = 1;
			high = n;

			while(low < high){
				int mid = low + (high-low)/2;
				int count = obj.getRookCount(1,1, n, mid);

				if(count == (mid - low + 1)){
					// search half after mid
					low = mid + 1;
				} else {
					// search in same half
					hi = mid;
				}

			}

			int col = row;
			return {row, col};
		}
};

int main() {
	int n = 8;
	Solution obj;
	auto res = obj.getNthRookPosition(n);
	return 0;
}

// Binary search

// Template 1 with <=

searching for an exact answer
partition problems
binary search on indices

while(low <= high)
{
    mid

    if(mid is answer)
        return;

    if(answer is left)
        high = mid - 1;
    else
        low = mid + 1;
}

// Template 2 with <

lower_bound
upper_bound
first true
last false
binary search on answer

while(low < high)
{
    mid

    if(answer <= mid)
        high = mid;
    else
        low = mid + 1;
}

return low;