#include <bits/stdc++.h>

int maxSumDivThree(std::vector<int>& nums) {
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 3 == 0) return sum;

    int r1a = INT_MAX, r1b = INT_MAX; // two smallest with residue 1
    int r2a = INT_MAX, r2b = INT_MAX; // two smallest with residue 2

    for (int x : nums) {
        int r = x % 3;
        if (r == 1) {
            if (x < r1a) { r1b = r1a; r1a = x; }
            else if (x < r1b) r1b = x;
        } else if (r == 2) {
            if (x < r2a) { r2b = r2a; r2a = x; }
            else if (x < r2b) r2b = x;
        }
    }

    int target = sum % 3;
    int remove = INT_MAX;
    if (target == 1) {
        // remove smallest residue-1, or sum of two smallest residue-2
        remove = std::min(r1a, (r2a == INT_MAX || r2b == INT_MAX) ? INT_MAX : r2a + r2b);
    } else { // target == 2
        // remove smallest residue-2, or sum of two smallest residue-1
        remove = std::min(r2a, (r1a == INT_MAX || r1b == INT_MAX) ? INT_MAX : r1a + r1b);
    }

    return (remove == INT_MAX) ? 0 : sum - remove;
}

int main(){
    std::vector<int> nums = {1,2,3,4,4};
    std::cout << maxSumDivThree(nums) << std::endl;
}