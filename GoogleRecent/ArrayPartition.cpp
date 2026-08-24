// Find the number of partitions of an array such that each contiguous partition consists of atleast one negative number.
// https://leetcode.com/discuss/post/4574669/google-onsite-find-partitions-by-apoorva-69td/

// Brute force
// we can cut or not cut at n-1 indexes to genrate partition, 2^n-1 partitions
// checking each for -ve value present or not x N wor
// O(N.2^N-1) not acceptable

// DP
// think of it like for index i, i can make partition at indexes i, i + 1, i + 2 till n-1 as long as they contain -ve
// if i reach the end of arr, it was a valid partition it means

int n;
vector<int> dp;

// O(N^2) TC and O(N) SC
long long solve(int idx, vector<int>& arr){
	if(idx == n) return 1; // valid partitions formed
	if(dp[idx] != -1) return dp[idx];

	bool hasNegative = false;
	for(int j = idx; j < n; j++){
		if(arr[j] < 0) hasNegative = true;
		if(hasNegative){
			// try this idx as segment end
			ans += solve(j+1, arr);
		}
	}

	return dp[idx] = ans;
}

long long countPartition(vector<int>& arr){
	n = nums.size();
	dp.assign(n, -1);
	return solve(0, arr);
}

// optimizing dp to O(1)
// once you encounter a -ve value every index from that point is a valid endpoint that can be tried for
// dp[i]= dp[k] + dp[k+1] + dp[k+2].... + dp[n], where k is the first index where we see -ve value
// we need to know firstNegative from current index, and sum of all dp values from that index to end (suffix sum)
// O(n) TC and SC
long long countPartition(vector<int>& arr){
	int n = nums.size();
	vector<long long> dp(n+1, 0);
	vector<long long> suffix(n+1, 0); // suffix sum is on dp array

	dp[n] = 1;
	suffix[n] = 1;
	int firstNegative = -1;

	// process in reverse order
	for(int i = n-1; i >= 0; i--){
		if(nums[i] < 0) firstNegative = i;

		if(firstNegative != -1){
			dp[i] = suffix[firstNegative + 1]; // same logic as in recursive method
		}

		// genric suffix sum approach
		suffix[i] = suffix[i+1] + dp[i];
	}

	return dp[0];
}

// suffix not needed actually
long long countPartition(vector<int>& nums) {
    int n = nums.size();

    long long suffixSum = 1; // equivalent to suffix[n]
    long long dp = 0;

    int firstNegative = -1;

    for (int i = n - 1; i >= 0; i--) {
        if (nums[i] < 0)
            firstNegative = i;

        if (firstNegative != -1) {
            dp = suffixSum;
        }

        suffixSum += dp;
    }

    return dp;
}

// non dp solution
// Between every pair of consecutive negative numbers, 
// you have a number of possible places where you can make the cut. Those choices are independent, so you multiply them.

long long findNumPartitions(vector<int>& arr) {
    long long ans = 1;

    int prevNeg = -1;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {

            // Consecutive negative numbers define a new
            // independent range of choices.
            if (prevNeg != -1) {
                ans *= (i - prevNeg + 1);
            }

            prevNeg = i;
        }
    }

    // No negative number => impossible to form a valid partition
    if (prevNeg == -1)
        return 0;

    return ans;
}