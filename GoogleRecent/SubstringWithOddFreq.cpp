// Longest Substring with At Most K Odd-Frequency Characters Given a string s and an integer K, 
// find the maximum length of a substring in which at most K distinct characters have an odd frequency.

// ab
// 11

// aba
// 10

// 0 - even
// 1 - odd

// substring mask
//     =
// prefix[r] XOR prefix[l]

// number of 1s in that XOR
//     =
// number of odd-frequency characters

// current number
//       ↓
// find something earlier in map
//       ↓
// that makes a valid pair

// current prefix mask
//       ↓
// find something earlier in map
//       ↓
// currentMask XOR previousMask has ≤ K bits

       //       PREFIX PARITY
       //            ↓
       //       current mask
       //            ↓
       //  ┌──────────────────┐
       //  │ flip 0 bits      │
       //  │ flip 1 bit       │
       //  │ flip 2 bits      │
       //  │ ...              │
       //  │ flip K bits      │
       //  └──────────────────┘
       //            ↓
       // possible previous masks
       //            ↓
       //       hashmap lookup
       //            ↓
       //    found previous mask?
       //       ↓          ↓
       //      YES         NO
       //       ↓
       // calculate length
       //       ↓
       //    maximize ans


class Solution {
    unordered_map<int, int> earliest; // track first seen index of a mask
    int ans = 0;

    void generate(int currMask, int k, int right, int idxFlip, int flips) {
        // If we have seen this mask before, update our max length
        if (earliest.find(currMask) != earliest.end()) {
            ans = max(ans, right - earliest[currMask]);
        }

        // Base case for recursion: stop if we've flipped 'k' bits
        if (flips == k) return;

        // Try flipping bits from idxFlip to 25 to generate combinations
        for (int i = idxFlip; i < 26; i++) {
            int nextMask = currMask ^ (1 << i);
            generate(nextMask, k, right, i + 1, flips + 1);
        }
    }

public:
    int longestSubstring(string s, int k) {
        // 1. CRITICAL: Reset class variables for multiple LeetCode test cases
        earliest.clear();
        ans = 0;

        // 2. Base case: at index -1, all characters have 0 (even) frequency
        earliest[0] = -1; 
        int mask = 0;

        for (int i = 0; i < s.size(); i++) {
            int bit = s[i] - 'a';
            
            // Toggle the bit for the current character
            mask ^= (1 << bit);

            // Generate all previous masks that differ by 0 to k bits
            generate(mask, k, i, 0, 0);

            // 3. Only save the mask if it's the EARLIEST time we've seen it
            // (We want the smallest index to maximize length)
            if (earliest.find(mask) == earliest.end()) {
                earliest[mask] = i; 
            }
        }

        return ans; // 4. Moved inside the function!
    }
};
