// https://leetcode.com/problems/smallest-all-ones-multiple/

class Solution {
public:
    int minAllOneMultiple(int k) {
        int rem = 0;
        for(int len = 1; len <=k ; len++){
            rem = (rem *10 + 1) % k;
            if(rem == 0){
                return len;
            }
        }
        return -1;
    }
};

// below code gives overflow

int minAllOneMultiple(int k) {
        int ans = -1;
        int x = 1;

        while(x <= std::numeric_limits<int>::max()){
            if(x%k==0){
                ans = k;
                break;
            }
            x = x*10 + 1;
        }
        
        if(ans == -1){
            return -1;
        }

        std::string str = std::to_string(ans);
        return str.size();
}

/*
===========================================================
STUDY NOTES: Why Modulo Prevents Overflow in All-Ones Multiple
===========================================================

Problem:
We want the smallest number consisting only of digit '1'
(1, 11, 111, 1111, ...) that is divisible by k.

Why the naive approach fails:
- Directly building the number using:
      x = x * 10 + 1
  makes x grow exponentially.
- Very quickly x exceeds INT_MAX (~2e9), causing integer
  overflow and undefined behavior.
- But for divisibility, we never need the full number.

Key Insight:
Divisibility depends only on the remainder (mod k), not on
the actual value of the number.

Modulo Property Used:
For any integers a, b, k:
      (a * 10 + b) % k = ((a % k) * 10 + b) % k

This allows us to build the number digit-by-digit while
keeping values small.

How it applies here:
Let rem = remainder of the current all-ones number mod k.

Start with rem = 0, and for each new '1':
      rem = (rem * 10 + 1) % k

- rem is always in range [0, k - 1]
- No overflow can ever occur
- When rem == 0, the constructed number is divisible by k

Why we loop only up to k times:
- There are only k possible remainders: 0 to k-1
- By the pigeonhole principle, if remainder 0 does not
  appear within k steps, remainders will start repeating
- Once repeating starts, we will loop forever
- Hence, if no solution in k steps, answer is -1

Mental Model:
"I am not building the number; I am simulating long division."

Complexity:
- Time:  O(k)
- Space: O(1)
- Overflow: Impossible

This is the mathematically correct and interview-expected
solution for this problem.
===========================================================
*/
