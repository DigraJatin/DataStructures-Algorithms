#include <bits/stdc++.h>

using std::vector;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        // Aproach 1 - Sorting - NLogn - Time, Constant space
        // sort(nums.begin(), nums.end());
        // for(int i = 0; i < nums.size() ; i++){
        // 	if(i>0 && nums[i]==nums[i-1])
        // 	{
        // 		return true;
        // 	}
        // }

        // Aproach 2 - N time, N Space
        std::unordered_map<int,int> dataSet;
        for(const auto &i:nums){
        	if(dataSet[i]==1){
        		return true;
        	}
        	dataSet[i]=1;
        }

        return false;
    }
};

class InputHelper {
public:
	vector<int> generateRandomInput() {
	    // Initialize random engine with seed
	    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

	    // Random length between 1 and 100000
	    std::uniform_int_distribution<int> lengthDist(1, 100000);
	    int length = lengthDist(rng);

	    // Random integers in range [-1e9, 1e9]
	    std::uniform_int_distribution<int64_t> valueDist(-1e9, 1e9);

	    vector<int> input;
	    input.reserve(length);

	    for (int i = 0; i < length; ++i) {
	        input.push_back(static_cast<int>(valueDist(rng)));
	    }

	    return input;
	}
};

int main(){
	vector<int> nums = InputHelper{}.generateRandomInput();
	std::cout<<"Input is :"<<std::endl;
	for(const auto &i: nums){
		std::cout<<i<<" ";
	}
	bool result = Solution{}.containsDuplicate(nums);
	std::cout<<std::endl<<"Result is :"<<result<<std::endl; 
	return 0;
}