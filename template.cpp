#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool sievofEratosthenes(int num) {
        bool retVal = true;
        for(int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                retVal = false;
                break;
            }
        }
        return retVal;   
    }

    bool completePrime(int num) {
        if(sievofEratosthenes(num) == false){
            return false;
        }
        std::string numStr = std::to_string(num);
        int n = numStr.size();
        
        int prefix = 0;
        for(int i = 0 ; i < n ; i++){
            prefix = prefix*10 + (numStr[i] - '0');
            if(sievofEratosthenes(prefix) == false){
                return false;
            }
        }

        int suffix = 0;
        int j = 0;
        for(int i = n-1 ; i >= 0 ; i--){
            int currDigit = (numStr[i] - '0');
            suffix = currDigit*pow(10,j) + suffix;
            if(sievofEratosthenes(suffix) == false){
                return false;
            }
            j++;
        }

        return true;   
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    int n = 1;
    std::cout<<sol.completePrime(n);

    return 0;
}
