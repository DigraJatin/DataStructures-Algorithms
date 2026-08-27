// Concept

// Instead of maintaining the exact median, group numbers into power-of-2 buckets:

// [1,2], [2,4], [4,8], [8,16], ...

// For every inserted number, store only its bucket count.

// To find the loose median, 
// find the bucket containing the median rank. Since a 32/64-bit integer has a fixed number of buckets, both operations are O(1).


class LooseMedian {
    vector<int> cnt;
    int n = 0;

public:
    LooseMedian() : cnt(32, 0) {}

    void insert(int num) {
        int k = floor(log2(num));   // bucket: [2^k, 2^(k+1)]
        cnt[k]++;
        n++;
    }

    int looseMedian() {
        int target = (n + 1) / 2; // we only need the bucket containing the median.
        int seen = 0;

        for (int k = 0; k < 32; k++) {
            seen += cnt[k];

            if (seen >= target)
                return 1 << k;     // valid loose median
            // can return (1 << (k+1) as well)
        }

        return -1;
    }
};

// Complexity
// insert() → O(1)
// looseMedian() → O(1), because there are only 32 buckets for positive 32-bit integers
// Space → O(1)