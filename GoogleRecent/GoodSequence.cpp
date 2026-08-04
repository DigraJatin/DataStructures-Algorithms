// Problem - An arithmetic sequence is a list of numbers with a definite pattern. If you take any number in the sequence then subtract it from the previous one, the difference is always a constant.

// A good arithmetic sequence is an arithmetic sequence with a common difference of either 1 or -1.

// For example, [4, 5, 6] is a good arithmetic sequence. So is [6, 5, 4], [10, 9], or [-3, -2, -1]. But, [1, 2, 1] (no common difference) or [3, 7] (common difference is 4) is NOT.
// Implied, any sequence that has only one element is a good arithmetic sequence.

// For example, [4] is a good arithmetic sequence.
// Given an integer array nums, return the sum of the sums of each subarray that is a good arithmetic sequence.

// Example:

// Given nums = [7, 4, 5, 6, 5]. Each of the following subarrays is a good arithmetic sequence:

// [7], [4], [5], [6], [5],
// [4, 5], [5, 6], [6, 5],
// [4, 5, 6]
// The sums of these subarrays are:

// 7, 4, 5, 6, 5,
// 4 + 5 = 9, 5 + 6 = 11, 6 + 5 = 11,
// 4 + 5 + 6 = 15
// Thus, the answer is the sum of all the sums above, which is:

// 7 + 4 + 5 + 6 + 5 + 9 + 11 + 11 + 15 = 73.

// [5 6 7 8 9]
// [6 7 8]

// an element L <= i <= R, the contribution of arr[i] to sum of all subarrays in [L, R] is (i - L + 1) * (R - i + 1) * arr[i]

int solve(vector<int>& arr){
	int n = arr.size();
	long long sum = accumulate(arr.begin(), arr.end(), 0LL);
	int left = 0, right = 0, cd = 0;

	// find sequences with cd 1
	cd = 1;
	right = 1;
	while(right < n){
		int d = arr[right] - arr[right - 1];
		if(d == cd){
			right++;
			if(right != n) continue;
		}

		// calculate contribution of each element[l, r-1]
		for(int i = left; i < right; i++){
			sum += arr[i] * (i - left + 1) * (right - 1 - i + 1) - arr[i];
		}
		left = right;
		right++;
	}

	// find seuences with cd -1
	cd = -1;
	left = 0;
	right = 1;
	while(right < n){
		int d = arr[right] - arr[right - 1];
		if(d == cd){
			right++;
			if(right != n) continue;
		}

		// calculate contribution of each element[l, r-1]
		for(int i = left; i < right; i++){
			sum += arr[i] * (i - left + 1) * (right - 1 - i + 1) - arr[i];
		}
		left = right;
		right++;
	}

	return sum;
}


// dp solution for single difference like 1 or -1

// For any index i, any valid subarray ending at i is either:

// Just the element itself: [arr[i]]
// The element arr[i] appended to all valid subarrays that ended at i-1.

// count: The number of valid subarrays ending at i-1.
// sumEndingHere: The total sum of all those valid subarrays ending at i-1.

// State Transitions:
// If arr[i] - arr[i-1] == d:

// The number of subarrays ending at i becomes count + 1 (the previous subarrays plus the single element [arr[i]]).

// The sum of these new subarrays becomes sumEndingHere + (arr[i] * new_count).

// If arr[i] - arr[i-1] != d:

// The streak is broken. The only valid subarray ending at i is just [arr[i]].

// count resets to 1.

// sumEndingHere resets to arr[i].

int solve(vector<int>& arr){
	int n = arr.size();
	long long ans = 0;

	// dp states for pev elemnts
	long long count = 1;
	long long sumEnding = arr[0];
	ans += sumEnding;

	for(int i = 1; i < n; i++){
		// extend prev subarrays
		if(arr[i] - arr[i-1] == 1){
			count++;
			sumEnding += (arr[i] * count);
		} else {
			count = 1;
			sumEnding = arr[i];
		}
		ans += sumEnding;
	}
	return ans;
}