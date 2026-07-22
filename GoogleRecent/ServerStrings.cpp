// You have M servers, each storing a list of string and it's frequency count
// [("abc", 3), ("xyz", 4) ....]
// M servers send their data to the central server

// on central server perform the operations :
// - Get top string have maximum frequency
// - Get top K strings having maximum frequency

// need to aggeregate the frequencies from M servers on the Main server

// M Servers
// N total no of pairs across all servers
// u - no of unique strings

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct Entry {
        string str;
        int freq;
    };

    Solution(const vector<vector<Entry>>& servers) {
        aggregateData(servers);
        buildHeap();
    }

    // O(1)
    string getTopString() {
        if (maxHeap.empty())
            return "";

        return maxHeap.top().str;
    }

    // O(U + K log U)
    vector<Entry> getTopKStrings(int k) {
        vector<Entry> ans;
        if (k <= 0)
            return ans;

        // Copy so original heap remains unchanged.
        auto pq = maxHeap;

        while (!pq.empty() && k--) {
            ans.push_back(pq.top());
            pq.pop();
        }

        return ans;
    }

private:
    struct Compare {
        bool operator()(const Entry& a, const Entry& b) const {
            return a.freq < b.freq;   // max heap
        }
    };

    void aggregateData(const vector<vector<Entry>>& servers) {
        for (const auto& server : servers) {
            for (const auto& entry : server) {
                freq[entry.str] += entry.freq;
            }
        }
    }

    void buildHeap() {
        for (const auto& [str, count] : freq) {
            maxHeap.push({str, count});
        }
    }

    unordered_map<string, int> freq;
    priority_queue<Entry, vector<Entry>, Compare> maxHeap;
};


