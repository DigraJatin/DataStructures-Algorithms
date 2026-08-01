// Question: Given an array of size "N", find 2 maximum sum non overlapping subarrays. 
// eg: array: [2,1,-99,3,3] output: 9 subarray 1:[2,1] subarray 2:[3,3] 

int solve(vector<int>& nums) {
    int n = nums.size();

    // rightMax[i] = Maximum subarray sum anywhere in the suffix [i...n-1].
    vector<int> rightMax(n);

    rightMax[n - 1] = nums[n - 1];
    int currStarting = nums[n - 1];

    for (int i = n - 2; i >= 0; i--) {
    	currStarting = max(nums[i], nums[i] + currStarting);
        rightMax[i] = max(rightMax[i + 1], currStarting);
    }

    // Traverse from left to right while maintaining:
    // currEnding = Maximum subarray sum ending at current index.
    // leftBest   = Maximum subarray sum anywhere in the prefix so far.
    int currEnding = nums[0];
    int leftBest = nums[0];

    int ans = INT_MIN;

    for (int i = 0; i < n - 1; i++) {
        if (i > 0) {
            currEnding = max(nums[i], currEnding + nums[i]);
            leftBest = max(leftBest, currEnding);
        }

        // Cut after index i.
        ans = max(ans, leftBest + rightMax[i + 1]);
    }

    return ans;
}

// Follow up question : In those maximum sum non overlapping subarrays the second subarray should be strictly increasing. 
// 1st subarray can be anything but 2nd one should be strictly increasing. but both should have maximum sum. 
// eg: array: [6,6,-100,6,7,1] output: 25 subarray 1:[6,6] subarray 2:[6,7]

for (int i = n - 2; i >= 0; i--) {
	if(nums[i+1] - nums[i] > 0){
        currStarting = max(nums[i], nums[i] + currStarting);
	} else {
        currStarting = nums[i];
	}
    rightMax[i] = max(rightMax[i + 1], currStarting);
}