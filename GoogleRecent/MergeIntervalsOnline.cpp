// Merge intervals Online
// https://enginebogie.com/interview/experience/google-software-development-engineer-3/166

// Design a system that can handle dynamic range updates and efficient range queries. Specifically, implement two functions:

// addRange(start, end) - Adds a new inclusive range [start, end] to the system.
// queryRange(value) - Returns true if the given value is included in any of the current ranges, otherwise returns false.
// The system should start with no ranges (empty). Overlapping or adjacent ranges should be merged appropriately during the addRange operations.

// Example 1:

// Initialize the system -> Total Range: []
// addRange(2, 4) -> Total Range: [[2,4]]
// addRange(5, 7) -> Total Range: [[2,4], [5,7]]
// queryRange(1) -> Output: false
// addRange(1, 9) -> Total Range: [[1,9]]
// queryRange(1) -> Output: true
// Example 2:

// Initialize the system -> Total Range: []
// addRange(1, 3) -> Total Range: [[1,3]]
// addRange(6, 9) -> Total Range: [[1,3], [6,9]]
// queryRange(4) -> Output: false
// addRange(2, 5) -> Total Range: [[1,5], [6,9]]
// queryRange(4) -> Output: true
// Constraints:
// The number of calls to addRange and queryRange functions is at most 10^4.
// 0 <= start <= end <= 10^9
// Each query and update operation should be efficient.

// Two intervals overlap iff

// existing.end >= new.start

// and

// existing.start <= new.end

#include <bits/stdc++.h>
using namespace std;

class RangeModule {
    // Always stores non-overlapping, merged intervals.
    set<pair<int, int>> intervals;

public:
    void addRange(int l, int r) {

        auto it = intervals.lower_bound({l, -1});

        // Previous interval may also overlap.
        if (it != intervals.begin())
            --it;

        while (it != intervals.end()) {

            // Completely before new interval.
            if (it->second + 1 < l) {
                ++it;
                continue;
            }

            // Since intervals are sorted, no future interval can overlap.
            if (it->first > r + 1)
                break;

            // Merge.
            l = min(l, it->first);
            r = max(r, it->second);

            it = intervals.erase(it);
        }

        intervals.insert({l, r});
    }

    bool queryRange(int x) {

        auto it = intervals.upper_bound({x, INT_MAX});

        if (it == intervals.begin())
            return false;

        --it;

        return it->first <= x && x <= it->second;
    }

    void print() {

        cout << "[ ";

        for (auto [l, r] : intervals)
            cout << "[" << l << "," << r << "] ";

        cout << "]\n";
    }
};

int main() {

    RangeModule rm;

    rm.addRange(2, 4);
    rm.print();          // [ [2,4] ]

    rm.addRange(5, 7);
    rm.print();          // [ [2,7] ] (adjacent merged)

    cout << boolalpha << rm.queryRange(1) << "\n"; // false

    rm.addRange(1, 9);
    rm.print();          // [ [1,9] ]

    cout << rm.queryRange(1) << "\n"; // true
}

// Complexity
// addRange()
// O((K+1) log N) worst case
// K = number of merged intervals
// queryRange()
// O(log N)
// Space
// O(N) (N = current merged intervals)

// Small interview trick

// Notice these two conditions:

// // Completely before
// if (it->second + 1 < l)

// // Completely after
// if (it->first > r + 1)

// If the problem doesn't merge adjacent intervals (like Range Module), simply change them to:

// if (it->second < l)
//     ++it;

// if (it->first > r)
//     break;