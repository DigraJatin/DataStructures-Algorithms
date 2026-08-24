#include <bits/stdc++.h>
using namespace std;

/*
 * Problem: Given a candidate interval and a set of existing intervals,
 * determine if the candidate conflicts with any existing interval.
 *
 * Semantics: Half-open intervals [start, end)
 *   - Two intervals [a,b) and [c,d) overlap iff: a < d AND c < b
 *   - Touching at a single point (e.g. [1,3) and [3,5)) is NOT a conflict
 *
 * Approach:
 *   Preprocess the interval set once in O(n log n):
 *     1. Sort intervals by start
 *     2. Build a prefix-max array over end values
 *
 *   Answer each query in O(log n):
 *     1. Binary search to find all intervals with start < candidate.end
 *     2. Check if the farthest-reaching end among them exceeds candidate.start
 *
 * Why prefix-max?
 *   After sorting by start, binary search gives us a prefix of intervals
 *   whose start < ce. But we can't just check the last one — an earlier
 *   interval might reach further (e.g. [1,10] followed by [2,4]).
 *   prefix-max[i] = max(end) over intervals[0..i], so a single O(1)
 *   lookup tells us the furthest any interval in the prefix reaches.
 *
 * Why not merge overlapping intervals?
 *   Merging would also work, but it's unnecessary extra work.
 *   The prefix-max achieves the same effect: it "covers" all overlapping
 *   intervals in the prefix without explicitly merging them.
 *
 * Complexity:
 *   Preprocess : O(n log n) time, O(n) space
 *   Per query  : O(log n)   time, O(1) space
 */

using ll = long long;
using Interval = pair<ll, ll>;   // [start, end)

struct IntervalIndex {
    vector<Interval> ivs;        // sorted by start
    vector<ll>       maxEnd;     // maxEnd[i] = max(end) over ivs[0..i]

    /*
     * Preprocess a list of intervals.
     * Sort by start, then build prefix-max over end values.
     *
     * Sorting ensures binary search is valid.
     * prefix-max ensures we don't miss an interval that started early
     * but reaches far (e.g. [1,100] followed by [2,3]).
     */
    IntervalIndex(vector<Interval> intervals) {
        ivs = move(intervals);
        sort(ivs.begin(), ivs.end());   // lexicographic: sort by start, tie-break by end

        maxEnd.reserve(ivs.size());
        ll curMax = LLONG_MIN;
        for (auto& [s, e] : ivs) {
            curMax = max(curMax, e);
            maxEnd.push_back(curMax);
        }
    }

    /*
     * Query: does candidate [cs, ce) conflict with any stored interval?
     *
     * Step 1: Binary search for first interval with start >= ce.
     *         All intervals from that point onward have start >= ce,
     *         so they cannot overlap [cs, ce) — overlap requires start < ce.
     *
     * Step 2: Everything to the LEFT of that iterator has start < ce.
     *         We only need to check if any of them has end > cs,
     *         because overlap also requires end > cs.
     *         maxEnd[idx] gives us the maximum end in that prefix — O(1).
     *
     * Why {ce, LLONG_MIN} as the search key?
     *   pair comparison is lexicographic. Using LLONG_MIN as the second
     *   element ensures lower_bound finds the FIRST pair whose .first >= ce,
     *   regardless of the .second value. Any other sentinel risks skipping
     *   valid intervals (e.g. {ce, 0} would miss intervals with end < 0).
     */
    bool hasConflict(Interval candidate) const {
        auto [cs, ce] = candidate;

        // iterator to first interval with start >= ce
        auto it = lower_bound(
            ivs.begin(), ivs.end(),
            Interval{ce, LLONG_MIN}
        );

        // all intervals start >= ce → none can overlap
        if (it == ivs.begin())
            return false;

        // index of last interval with start < ce
        // using pointer arithmetic — O(1) for random-access iterators
        ll idx = (it - ivs.begin()) - 1;

        // if the farthest-reaching end in this prefix exceeds cs,
        // that interval overlaps [cs, ce)
        return maxEnd[idx] > cs;
    }
};

// ---------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------

int main() {
    // Each test: {candidate, intervals, expected}
    struct Test {
        Interval         candidate;
        vector<Interval> intervals;
        bool             expected;
        string           description;
    };

    vector<Test> tests = {
        // Basic no-conflict: touching at endpoint
        {
            {4, 7},
            {{1, 3}, {7, 9}},
            false,
            "touching endpoints are not a conflict"
        },
        // Basic conflict: partial overlap
        {
            {4, 7},
            {{1, 5}, {8, 9}},
            true,
            "partial overlap on the left"
        },
        // Candidate fully contained inside an existing interval
        {
            {4, 6},
            {{1, 10}},
            true,
            "candidate fully inside existing interval"
        },
        // Existing interval fully contained inside candidate
        {
            {1, 10},
            {{3, 5}},
            true,
            "existing interval fully inside candidate"
        },
        // Equal start
        {
            {4, 7},
            {{4, 9}},
            true,
            "equal start counts as overlap"
        },
        // Empty interval list
        {
            {4, 7},
            {},
            false,
            "empty interval list"
        },
        // Candidate before all intervals
        {
            {1, 3},
            {{5, 10}, {8, 12}},
            false,
            "candidate entirely before all intervals"
        },
        // Candidate after all intervals
        {
            {15, 20},
            {{1, 5}, {6, 10}},
            false,
            "candidate entirely after all intervals"
        },
        // Overlapping existing intervals (no merge needed)
        {
            {5, 7},
            {{1, 10}, {2, 4}, {8, 12}},
            true,
            "existing intervals overlap each other, candidate conflicts with first"
        },
        // Large values (signed 64-bit boundary)
        {
            {LLONG_MIN, 0},
            {{-1, LLONG_MAX}},
            true,
            "large signed 64-bit values"
        },
    };

    int passed = 0;
    for (auto& t : tests) {
        IntervalIndex idx(t.intervals);
        bool result = idx.hasConflict(t.candidate);
        bool ok     = (result == t.expected);
        passed     += ok;

        cout << (ok ? "PASS" : "FAIL")
             << " | " << t.description
             << " | got=" << result
             << " expected=" << t.expected
             << "\n";
    }

    cout << "\n" << passed << "/" << tests.size() << " tests passed\n";
    return (passed == (int)tests.size()) ? 0 : 1;
}


