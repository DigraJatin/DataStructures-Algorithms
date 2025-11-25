#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
vector<int> topKFrequent(vector<int>& nums, int k) {
    if(k == nums.size()){
        return nums;
    }

    vector<int> result;
    unordered_map<int,int> mp;
    for(const auto &i : nums){
        mp[i]++;
    }

    // 2. Define a custom comparator lambda function for a min-heap
    // The comparator uses the frequencies stored in 'mp' to order elements.
    // It is a min-heap based on frequency: the element with the lowest frequency goes to the top.
    auto comp = [&mp](int n1, int n2) { return mp[n1] > mp[n2]; };
    
    // 3. Declare the priority queue (min-heap) using the custom comparator
    priority_queue<int, vector<int>, decltype(comp)> heap(comp);

    // 4. Populate the heap and maintain size 'k'
    for(auto const& [num, freq] : mp) {
        heap.push(num);
        if(heap.size() > k){
            // If the heap has more than k elements, remove the top one.
            // Since it's a min-heap, this removes the element with the *lowest* frequency,
            // keeping only the top k most frequent elements in the heap.
            heap.pop();
        }
    }

    // 5. Extract results from the heap
    // The remaining elements in the heap are the top K most frequent numbers.
    while(!heap.empty()){
        result.push_back(heap.top());
        heap.pop();
    }

    // Optional: The problem doesn't specify order, but you might want to reverse
    // the list if you want them ordered from most to least frequent.
    // std::reverse(result.begin(), result.end()); 
    
    return result;    
}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<int> nums = {1,2,1,2,1,2,3,1,3,2};
    int k = 2;
    vector<int> result = sol.topKFrequent(nums, k);
    for (int num : result) {
        cout << num << " ";
    }

    return 0;
}
