#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestRepunitDivByK(int k) {
        int remainder = 0;
        for (int i = 1; i<=k ; i++){
            int n = (remainder*10)+1;
            remainder = n % k;
            if(remainder == 0)
                return i;
        }
        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    auto result = sol.smallestRepunitDivByK(3);
    cout << result << "\n";

    return 0;
}
