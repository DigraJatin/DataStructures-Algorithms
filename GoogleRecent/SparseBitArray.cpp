// https://leetcode.com/discuss/post/4834179/google-l4-onsite-by-anonymous_user-eqlw/



#include <vector>

// Assuming the API is available
extern int query(int L, int R);

// Standard recursive helper function
void findOnesRecursive(int L, int R, std::vector<int>& res) {
    // If range is invalid or there are no 1s in this range, stop exploring
    if (L > R || query(L, R) == 0) {
        return;
    }
    
    // If we narrowed it down to a single element, we found a 1
    if (L == R) {
        res.push_back(L);
        return;
    }
    
    // Divide the current range in half and search both halves
    int mid = L + (R - L) / 2;
    
    findOnesRecursive(L, mid, res);
    findOnesRecursive(mid + 1, R, res);
}

// Main function to call
std::vector<int> getOnes(int M) {
    std::vector<int> res;
    
    if (M > 0) {
        findOnesRecursive(0, M - 1, res);
    }
    
    return res;
}

// follow up - optimized O(1) solution

#include <vector>

extern int query(int L, int R);

std::vector<int> getOnesOptimal(int M) {
    std::vector<int> res;
    int start = 0;
    
    while (start < M) {
        // Check if there are any 1s left in the remaining portion
        if (query(start, M - 1) == 0) {
            break;
        }
        
        int low = start;
        int high = M - 1;
        
        // FFFFTTTTT Binary Search for the first '1' in [start, M - 1]
        while (low < high) {
            int mid = low + (high - low) / 2;
            
            // Condition: Does [low, mid] contain a 1?
            if (query(low, mid) == 1) { // True
                high = mid;
            } else { // False
                low = mid + 1;
            }
        }
        
        // 'low' now points to the first 1 in the current segment
        res.push_back(low);
        
        // Move the pointer past the 1 we just found
        start = low + 1;
    }
    
    return res;
}

// 1. Recursive Divide and Conquer
// TC: O(K log M) - Prune empty branches; traverse at most log M levels
//     to reach each of the K ones.
// SC: O(log M) - Recursion stack reaches a maximum depth of log M.
//
// 2. Optimal Iterative Binary Search
// TC: O(K log M) - Perform a binary search taking O(log M) queries
//     for each of the K consecutive ones.
// SC: O(1) - Uses only a few integer pointers; no recursion stack.