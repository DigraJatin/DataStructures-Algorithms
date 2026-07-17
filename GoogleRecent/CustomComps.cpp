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

// good problem on using custom comp for sort

class Solution {
public:
    struct comp {
        int ranks;
        vector<vector<int>> counts;

        comp(int _rank, vector<vector<int>>& _counts)
            : ranks(_rank), counts(_counts) {}

        bool operator()(char a, char b) {
            // true -> a comes before b
            // false -> a comes after b
            // relate above core of compartor logic to our sorting requirement
            for(int i = 0; i < ranks; i++){
                if(counts[a-'A'][i] != counts[b-'A'][i]){
                    return counts[a-'A'][i] > counts[b-'A'][i];
                }
            }

            return a < b ; // lexographical order if smaller comes first
        }
    };

    string rankTeams(vector<string>& votes) {
        int voters = votes.size();
        int ranks = votes[voters - 1].size();

        vector<vector<int>> counts(26, vector<int>(ranks, 0));
        for (auto& vote : votes) {
            for (int i = 0; i < ranks; i++) {
                counts[vote[i] - 'A'][i]++;
            }
        }

        string retVal =
            votes[0]; 
            // just take all teams in any initial order, does not
            // matter ACYXGZ, just need all chars to sort them

        // need to sort on the basis pos 1 > pos 2 > pos 3 .... lexo
        sort(retVal.begin(), retVal.end(), comp(ranks, counts));
        return retVal;
    }
};