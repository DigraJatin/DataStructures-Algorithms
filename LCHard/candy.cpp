#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int candy(vector<int>& r) {
        int n = r.size();
        vector<int> candies(n,1);

        // left neighbour pass
        for(int i = 1; i < n; i++){
            if(r[i] > r[i-1]){
                candies[i] = candies[i-1] + 1;
            }
        }
        // right
        for(int j = n-2; j>=0; j--){
            if(r[j] > r[j+1]){
                candies[j] = max(candies[j], candies[j+1]+1);
            }
        }

        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<int> r1 = {1,0,2};
    std::cout << sol.candy(r1);
    return 0;
}
