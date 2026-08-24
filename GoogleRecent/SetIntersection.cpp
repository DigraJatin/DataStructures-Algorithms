// https://leetcode.com/discuss/post/8195741/google-phone-screen-question-by-anonymou-yy9o/

#include <bits/stdc++.h>
using namespace std;

/*
    Returns:
    - index of the set to remove
    - maximum possible intersection after removal

    N = number of sets
    T = total number of elements across all sets
    K = number of elements having frequency N - 1

    Time:
        O(T + K * N)

        O(T)       -> build frequency map
        O(K * N)   -> find which set is missing each
                      almost-common element

        Worst case: O(T * N)

    Space:
        O(U + N)

        U = number of distinct elements
*/
pair<int, unordered_set<int>>
solve(const vector<unordered_set<int>>& sets) {

    int n = sets.size();

    if (n <= 1)
        return {-1, {}};

    // --------------------------------------------------
    // Step 1: Count how many sets contain each element
    // --------------------------------------------------

    // freq[x] = number of sets containing x
    unordered_map<int, int> freq;

    // O(T)
    for (int i = 0; i < n; i++) {
        for (int x : sets[i]) {
            freq[x]++;
        }
    }

    // --------------------------------------------------
    // Step 2: Find which set is blocking each
    // almost-common element
    //
    // If freq[x] == n - 1, x is missing from exactly
    // one set. Removing that set makes x common.
    // --------------------------------------------------

    // missingSet[x] = index of the set missing x
    unordered_map<int, int> missingSet;

    // O(K * N) average
    for (auto& [x, count] : freq) {

        if (count == n - 1) {

            for (int i = 0; i < n; i++) {

                if (sets[i].find(x) == sets[i].end()) {
                    missingSet[x] = i;
                    break;
                }
            }
        }
    }

    // --------------------------------------------------
    // Step 3: Score each set
    //
    // score[i] = number of almost-common elements
    //            that become common if set i is removed
    // --------------------------------------------------

    vector<int> score(n, 0);

    for (auto& [x, missingIdx] : missingSet) {
        score[missingIdx]++;
    }

    // --------------------------------------------------
    // Step 4: Find the best set to remove
    // --------------------------------------------------

    int bestRemoveIdx = 0;

    for (int i = 1; i < n; i++) {

        if (score[i] > score[bestRemoveIdx]) {
            bestRemoveIdx = i;
        }
    }

    // --------------------------------------------------
    // Step 5: Build final intersection
    // --------------------------------------------------

    unordered_set<int> finalIntersection;

    for (auto& [x, count] : freq) {

        // Present in every set -> always remains
        if (count == n) {
            finalIntersection.insert(x);
        }

        // Present in n-1 sets -> remains only if
        // we remove the set that is missing x
        else if (count == n - 1 &&
                 missingSet[x] == bestRemoveIdx) {

            finalIntersection.insert(x);
        }
    }

    return {bestRemoveIdx, finalIntersection};
}

// removing the K X N bottle neck
// instead of checking every set for x, if it's the one missing it's nth occ
// use XOR which is reversible

// a ^ b = c -> a = b ^ c

// missing = totalXor ^ xorIdx[x]
// totalXor = 0 ^ 1 ^ 2 ...... ^ n-1
// maintain xorIdx[x] while computing the frequency itself, no need of K.N loop

unordered_map<int, int> freq;
unordered_map<int, int> xorIdx;

// O(T)
for (int i = 0; i < n; i++) {
    for (int x : sets[i]) {
        freq[x]++;
        xorIdx[x] ^= i;
    }
}

// XOR of all set indices
int totalXor = 0;

for (int i = 0; i < n; i++)
    totalXor ^= i;


vector<int> score(n, 0);

// Find how many almost-common elements
// each set is missing.
for (auto& [x, count] : freq) {

    if (count == n - 1) {

        int missingSet = totalXor ^ xorIdx[x];

        score[missingSet]++;
    }
}