#include <bits/stdc++.h>

using namespace std;

vector<bool> prefixesDivBy5(vector<int>& nums) {
    int n = nums.size();
    vector<bool> res(n, false);
    int curr = 0;

    for(int i = 0 ; i < n ; i++){
        curr = ((curr << 1) + nums[i]) % 5;
        res[i] = curr % 5 == 0 ? true : false;
    }

    return res;
}

int main(){
    vector<int> nums = {0,1,1,1,1,1};
    vector<bool> result = prefixesDivBy5(nums);
    for(bool val : result){
        cout << (val ? "true" : "false") << " ";
    }
    return 0;
}