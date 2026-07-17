#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
	int minSwaps(const vector<int>& arr, int k){
		int n = arr.size();
		int windowSize = 0;
		for(int i = 0; i < n; i++){
			if(arr[i] <= k) windowSize++;
		}

		if(windowSize == 0 || windowSize == arr.size()) return 0;

		// form the first window
		int badElements = 0;
		for(int i = 0; i < windowSize; i++){
			if(arr[i] > k) badElements++;
		}

		int ans = badElements;
		// slide the window
		// i is the index leaving the window, j is the index adding to the window
		for(int i = 0, j = windowSize; j < arr.size(); i++, j++){
			if(arr[i] > k) badElements--;
			if(arr[j] > k) badElements++;

			ans = min(ans, badElements);
		}

		return ans; 
	}

	int minSwapsCircular(const vector<int>& arr, int k){
		int n = arr.size();
		int windowSize = 0;
		for(int i = 0; i < n; i++){
			if(arr[i] <= k) windowSize++;
		}

		if(windowSize == 0 || windowSize == arr.size()) return 0;

		// form the first window
		int badElements = 0;
		for(int i = 0; i < windowSize; i++){
			if(arr[i] > k) badElements++;
		}

		int ans = badElements;
		// slide the window
		// i is the index leaving the window, j is the index adding to the window
		int limit = n + windowSize - 1;
		for(int i = 0, j = windowSize; j < limit; i++, j++){
			if(arr[i % n] > k) badElements--;
			if(arr[j % n] > k) badElements++;

			ans = min(ans, badElements);
		}

		return ans; 
	}
};
