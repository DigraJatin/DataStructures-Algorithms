// Version 1 (Most likely)
// Problem Statement

// Given:

// An integer array nums
// A starting index start
// An integer x

// Initially, your current position is start.

// For round i = 1,2,3,...

// If i is odd:
// Search to the left of the current position.
// Find the nearest index whose value equals 2 * nums[current].
// If i is even:
// Search to the right of the current position.
// Find the nearest index whose value equals 2 * nums[current].

// If no such index exists, stop.

// Otherwise

// Increase
// nums[current] += x;
// Move to the found index.

// Repeat.

// brute force O(k X n) k is no of rounds, just simulate

// optimized, maintain value -> ordered set of indexes mapping
void solve(vector<int>& nums, int start, int x){
	unordered_map<int, set<int>> mp;
	int n = nums.size();

	for(int i = 0; i < n; i++){
		mp[nums[i]].insert(i);
	}

	int curr = start;
	int round = 1;

	while(1){
		int target = nums[curr] * 2;
		if(mp.find(target) == mp.end()) break; // no next round possible

		auto searchSpace = mp[target];
		int next = -1;

		if(round % 2 != 0){
			// odd, search left
			auto it = searchSpace.lower_bound(curr);
			if(it == searchSpace.begin()) break; // not found
			--it;
			next = *it;
		} else {
			auto it = searchSpace.upper_bound(curr);
			if(it == searchSpace.end()) break;
			next = *it;
		}

		mp[nums[curr]].erase(curr);
		nums[curr] += x;
		mp[nums[curr]].insert(curr);
		curr = next;
		round++;
	}
}

// Building O(n log n), rest are O(1) or O(log n)
// Overall O(nlogn)

// Function,Condition,What it actually finds
// lower_bound(x),>= x,"The first element that is equal to x (or greater, if x is missing)."
// upper_bound(x),> x,The first element that is strictly greater than x.

// Case 2 if value update with +x was not required just unordered_map<int, vector<int>> would work.
// O(n) building
// Each round O(log n)
// Worst case O(nlogn)