// You are given a replacements mapping and a text string that may contain placeholders formatted as %var%, where each var corresponds to a key in the replacements mapping. Each replacement value may itself contain one or more such placeholders. Each placeholder is replaced by the value associated with its corresponding replacement key.

// Your task is to return the fully substituted text string which does not contain any placeholders.

// The key challenge here is that replacement values can themselves contain placeholders that need to be resolved. This means you need to recursively substitute placeholders until no more remain.

// Example:
// replacements = {{"name","bob"}, {"greeting","hello %name%"}}
// text = "%greeting%!"
// Output = "hello bob!"

// Approach:
// DFS Recursion + Memoization + Cycle Detection

// Time Complexity:
// O(T)
// T = Total length of all replacement strings + input text.
// Each variable is resolved only once (memoization) and every character
// is scanned a constant number of times.

// Space Complexity:
// O(T + N)
// Memoized expanded strings + recursion stack + hash maps.
// N = Number of variables.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class Solution {
private:
    unordered_map<string, string> replacements;
    unordered_map<string, string> memo;
    unordered_map<string, int> state;
    // 0 = UNVISITED
    // 1 = VISITING
    // 2 = RESOLVED

    // Expand every %var% inside an arbitrary string
    string expandText(const string &text) {
        string result;

        for (int i = 0; i < text.size();) {

            if (text[i] != '%') {
                result += text[i++];
                continue;
            }

            int j = i + 1;
            while (j < text.size() && text[j] != '%')
                j++;

            if (j == text.size())
                throw runtime_error("Invalid placeholder");

            string var = text.substr(i + 1, j - i - 1);

            result += resolve(var);

            i = j + 1;
        }

        return result;
    }

    // DFS + Memoization
    string resolve(const string &var) {

        if (memo.count(var))
            return memo[var];

        if (!replacements.count(var))
            throw runtime_error("Undefined variable: " + var);

        if (state[var] == 1)
            throw runtime_error("Cycle detected");

        state[var] = 1;

        string expanded = expandText(replacements[var]);

        state[var] = 2;

        return memo[var] = expanded;
    }

public:
    string substitute(vector<pair<string, string>> &mapping,
                      const string &text) {

        replacements.clear();
        memo.clear();
        state.clear();

        for (auto &p : mapping)
            replacements[p.first] = p.second;

        return expandText(text);
    }
};

int main() {

    vector<pair<string, string>> replacements = {
        {"name", "bob"},
        {"greeting", "hello %name%"},
        {"city", "New York"},
        {"message", "%greeting%! Welcome to %city%."}
    };

    string text = "%message%";

    Solution sol;

    try {
        cout << sol.substitute(replacements, text) << '\n';
    }
    catch (const exception &e) {
        cout << e.what() << '\n';
    }

    return 0;
}

// Topo sort

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class Solution {
public:
    string substitute(vector<pair<string, string>>& mapping, string text) {

        unordered_map<string, string> value;               // current value of each variable
        unordered_map<string, vector<string>> graph;       // dependency -> dependents
        unordered_map<string, int> indegree;

        // Store original strings
        for (auto& [var, str] : mapping) {
            value[var] = str;
            indegree[var] = 0;
        }

        // Build graph
        for (auto& [var, str] : mapping) {

            unordered_set<string> seen;

            for (int i = 0; i < str.size();) {

                if (str[i] != '%') {
                    i++;
                    continue;
                }

                int j = i + 1;
                while (j < str.size() && str[j] != '%')
                    j++;

                string dep = str.substr(i + 1, j - i - 1);

                // Avoid duplicate edges
                if (!seen.count(dep)) {
                    graph[dep].push_back(var);
                    indegree[var]++;
                    seen.insert(dep);
                }

                i = j + 1;
            }
        }

        queue<string> q;

        for (auto& [var, deg] : indegree)
            if (deg == 0)
                q.push(var);

        int processed = 0;

        while (!q.empty()) {

            string curr = q.front();
            q.pop();
            processed++;

            for (string& nxt : graph[curr]) {

                replacePlaceholder(value[nxt], curr, value[curr]);

                indegree[nxt]--;

                if (indegree[nxt] == 0)
                    q.push(nxt);
            }
        }

        if (processed != mapping.size())
            throw runtime_error("Cycle detected");

        // Expand final text
        return expandText(text, value);
    }

private:

    static void replacePlaceholder(string& text,
                                   const string& var,
                                   const string& replacement) {

        string token = "%" + var + "%";

        size_t pos = 0;

        while ((pos = text.find(token, pos)) != string::npos) {
            text.replace(pos, token.size(), replacement);
            pos += replacement.size();
        }
    }

    static string expandText(const string& text,
                             unordered_map<string, string>& value) {

        string ans;

        for (int i = 0; i < text.size();) {

            if (text[i] != '%') {
                ans += text[i++];
                continue;
            }

            int j = i + 1;
            while (j < text.size() && text[j] != '%')
                j++;

            string var = text.substr(i + 1, j - i - 1);

            ans += value[var];

            i = j + 1;
        }

        return ans;
    }
};

int main() {

    vector<pair<string, string>> mapping = {
        {"name", "bob"},
        {"city", "New York"},
        {"greeting", "hello %name%"},
        {"message", "%greeting%! Welcome to %city%."}
    };

    string text = "%message%";

    Solution sol;

    cout << sol.substitute(mapping, text) << endl;

    return 0;
}

// Complexity

// Let:

// N = number of variables
// E = dependency edges
// L = total length of all replacement strings + input text

// Time Complexity

// Build graph: O(L)
// Topological sort: O(N + E)
// Placeholder replacements: each occurrence is replaced once over the whole process, so overall O(L) (ignoring the internal cost of string shifting for simplicity in interview analysis).

// Overall: O(L + N + E)

// Space Complexity

// Graph: O(N + E)
// Indegree map: O(N)
// Stored replacement strings: O(L)
// Queue: O(N)

// Overall: O(L + N + E)

// Which solution would I recommend?

// For this problem:

// ✅ DFS + Memoization is the cleaner and more natural solution. 
// It's shorter, easier to explain, and is likely what most interviewers expect first.
// ✅ Topological Sort is an excellent follow-up to show you recognize the dependency graph 
// and can eliminate recursion if needed. It demonstrates breadth, but it's noticeably more bookkeeping-heavy.