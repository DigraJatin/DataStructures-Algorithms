#include <bits/stdc++.h>
using namespace std;

/*
==========================================
SORT COMPARATOR
==========================================

Comparator answers:
    "Should 'a' come BEFORE 'b'?"

return a < b  --> Ascending
return a > b  --> Descending

Pass an OBJECT:
    sort(v.begin(), v.end(), comp());

*/

struct compSort {
    bool operator()(const pair<int,int>& a,
                    const pair<int,int>& b) const {

        if (a.first != b.first)
            return a.first > b.first;   // Efficiency DESC

        return a.second > b.second;     // Speed DESC
    }
};


/*
==========================================
PRIORITY QUEUE COMPARATOR
==========================================

Comparator answers:
    "Does 'a' have LOWER PRIORITY than 'b'?"

return a < b  --> Max Heap
return a > b  --> Min Heap

Pass the TYPE:
    priority_queue<int, vector<int>, compMin> pq;

*/

struct compMin {
    bool operator()(int a, int b) const {
        return a > b;      // Min Heap
    }
};

struct compMax {
    bool operator()(int a, int b) const {
        return a < b;      // Max Heap (same as default)
    }
};

int main() {

    vector<pair<int,int>> v = {
        {8,10}, {5,4}, {8,6}, {9,3}
    };

    // Sort by efficiency DESC, then speed DESC
    sort(v.begin(), v.end(), compSort());

    // Default Max Heap
    priority_queue<int> maxHeap;

    // Custom Min Heap
    priority_queue<int, vector<int>, compMin> minHeap;

    return 0;
}