#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to check if a number is prime using the Sieve of Eratosthenes method
    bool sievofEratosthenes(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    // Function to check if a number is palindrome
    bool isPalindrome(int num) {
        string strNum = to_string(num);
        int left = 0;
        int right = strNum.length() - 1;
        while (left < right) {
            if (strNum[left] != strNum[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    // Function to check if a number is perfect square
    // Using sqrt function, works safely for int range
    bool isPerfectSquare(int num) {
        if (num < 0) return false;
        int root = static_cast<int>(std::sqrt(num));
        return 1LL * root * root == num;
    }

    // Overloaded function to check if a number is perfect square for long long range
    bool isPerfectSquare(long long num) {
        if (num < 0) return false;

        if (num == 0) return true;
        long long lo = 1, hi = num;

        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;

            if (mid <= num / mid) {
                if (mid * mid == num) return true;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return false;
    }

    // Function to compute the floor of the square root of a number
    long long floorSqrt(long long r) {
        if (r == 0) return 0;

        long long lo = 1, hi = r, ans = 0;

        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;

            if (mid <= r / mid) {   // safe now (mid >= 1)
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }


    // Function to check if a number is a power of two
    bool isPowerOfTwo(int num) {
        if (num <= 0) return false;
        return (num & (num - 1)) == 0;
    }

    // Function to generate all divisors of a number
    vector<int> genrateDivisors(int num) {
        vector<int> divisors;
        for (int i = 1; i * i <= num; i++) {
            if (num % i == 0) {
                divisors.push_back(i);
                if (i != num / i) {
                    divisors.push_back(num / i);
                }
            }
        }
        sort(divisors.begin(), divisors.end());
        return divisors;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution solution;

    // call to solving functions can be placed here

    return 0;
}
