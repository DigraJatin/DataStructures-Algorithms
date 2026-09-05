// Kth largest element in array using quickselect
// https://leetcode.com/problems/kth-largest-element-in-an-array/description/

// Problem: Given a chat log file, find the top N most talkative users along with their total word count.

// Example Log:

// 10:00 < John > Hi, How is everyone?
// 10:05 < Amy > Hello John
// 10:06 < Maria > Great, Having my morning coffee
// 13:00 < John > Let's meet this weekend
// 13:30 < Amy > Woahoo
// Helper Function Provided:

// parseLog(filepath): Returns the word count of each message.
// Example Output:
// [{'John', 4}, {'Amy', 2}, {'Maria', 5}, {'John', 4}, {'Amy', 1}]
// Follow-up Questions:

// Optimize for better complexity.
// Implement the parseLog() function.

vector<pair<string, int>> topTalkative(
    const vector<string>& logs, int N) {

    unordered_map<string, int> total;

    // Parse + aggregate
    for (const string& line : logs) {
        stringstream ss(line);

        string time, open, user, close;
        ss >> time >> open >> user >> close;

        string word;
        int words = 0;

        while (ss >> word)
            words++;

        total[user] += words;
    }

    // Top N
    using P = pair<int, string>;

    priority_queue<P, vector<P>, greater<P>> pq;

    for (auto& [user, words] : total) {
        pq.push({words, user});

        if (pq.size() > N)
            pq.pop();
    }

    vector<pair<string, int>> ans;

    while (!pq.empty()) {
        auto [words, user] = pq.top();
        pq.pop();

        ans.push_back({user, words});
    }

    reverse(ans.begin(), ans.end());

    return ans;
}