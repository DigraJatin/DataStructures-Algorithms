// Finding first T in, FFFFTTTTTT
// while (lo < hi) {
//     mid = lo + (hi - lo) / 2;

//     if (isTrue(mid))
//         hi = mid;
//     else
//         lo = mid + 1;
// }

// return lo;


class Solution {
    bool isTrue(int x, int k, vector<vector<int>>& mat){
        int count = 0;
        int m = mat.size(), n = mat[0].size();
        int row = m-1, col = 0;

        while(row >= 0 && col < n){
            if(mat[row][col] <= x){
                count += row + 1;
                col++;
            } else {
                row--;
            }
        }

        return count >= k;
    }

public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        // count(x) = no of elements <= k
        // FFFFTTTTT 
        // need to find the first T i.e, 
        // first time when Count(x) >= k
        int low = matrix[0][0], high = matrix[m-1][n-1];

        while(low < high){
            int mid = low + (high-low)/2;
            if(isTrue(mid, k, matrix)){
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};

// O((m+n)log(range)) range = maxValue - minValue

// "The matrix never changes, but we might receive thousands/millions of different k queries."

// Sorting in preprocessing with O((m*n) * log(m*n)) is better than as ans is just sorted[k-1] and is O(1), trade off is huge memory



// Painters partition problem
// same FFFFTTTTT

bool isTrue(int time, const vector<int>& arr, int k) {
    int painters = 1;
    int curr = 0;

    for (int x : arr) {
        if (curr + x <= time) {
            curr += x;
        } else {
            painters++;
            curr = x;
        }
    }

    return painters <= k;
}

int painter_partition(const vector<int>& arr, int k) {
    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    while (low < high) {
        int mid = low + (high - low) / 2;

        if (isTrue(mid, arr, k))
            high = mid;
        else
            low = mid + 1;
    }

    return low;
}


// Painter Partition
// → minimize maximum load

// Book Allocation
// → minimize maximum pages

// Split Array Largest Sum
// → minimize maximum subarray sum

// Answer space:

// FFFFF | TTTTT
//       ↑
//    first T

// FFFFTTTT
//     ↑
//   first T



// T T T T F F F
//       ↑
//     last T

// Last T: T T T T F F F
// while (lo < hi) {
//     int mid = lo + (hi - lo + 1) / 2;  // upper mid

//     if (isTrue(mid))
//         lo = mid;
//     else
//         hi = mid - 1;
// }

// return lo;

bool contains(int x) {
    int lo = 0, hi = intervals.size() - 1;

    // Find LAST T:
    // intervals[i][0] <= x
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;  // upper mid

        if (intervals[mid][0] <= x)
            lo = mid;        // mid could be the answer
        else
            hi = mid - 1;    // mid is definitely not the answer
    }

    return intervals[lo][1] >= x;
}