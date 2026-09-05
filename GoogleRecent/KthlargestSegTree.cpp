// we have stream of integers
// but k is changing with every input

// we have a stream of integers, values can lie in -10^9 to 10^9
// we can create a segment tree on this range
// each node of tree stores the number of elements falling in that range
// every node stores frequency of the element

class Solution {
    static const int SHIFT = 10000;
    static const int MAXV = 20001; // Handles range [-10000, 10000] mapped to [0, 20000]
    vector<int> tree;

    void update(int node, int left, int right, int pos) {
        if (left == right) {
            tree[node]++;
            return;
        }

        int mid = left + (right - left) / 2;
        if (pos <= mid)
            update(2 * node, left, mid, pos);
        else
            update(2 * node + 1, mid + 1, right, pos);
            
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int queryKth(int node, int left, int right, int k) {
        // Base case: narrowed down to a single value
        if (left == right) {
            return left; 
        }

        int mid = left + (right - left) / 2;
        int right_count = tree[2 * node + 1];

        if (k <= right_count) {
            // The kth largest is in the right half
            return queryKth(2 * node + 1, mid + 1, right, k);
        } else {
            // Skip the right half, look for remaining k in the left half
            return queryKth(2 * node, left, mid, k - right_count);
        }
    }

public:
    Solution() {
        tree.assign(MAXV * 4, 0);
    }

    void insert(int num) {
        // Convert actual value to Segment Tree position
        int position = num + SHIFT;
        update(1, 0, MAXV - 1, position);
    }

    int getKthLargest(int k) {
        if (k > tree[1] || k <= 0) {
            return -1; // Or throw an error depending on requirements
        }
        
        // Find the shifted position of the kth largest
        int pos = queryKth(1, 0, MAXV - 1, k);
        
        // Un-shift to get the actual original value
        return pos - SHIFT;
    }
};