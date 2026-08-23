#include <bits/stdc++.h>
using namespace std;

struct Node {
    unordered_map<string, Node*> children;
    int score = 0;
};

vector<string> split(const string& s) {
    vector<string> parts;
    string cur;

    for (char c : s) {
        if (c == '.') {
            parts.push_back(cur);
            cur.clear();
        } else {
            cur += c;
        }
    }

    parts.push_back(cur);
    return parts;
}

void dfs(Node* node, int pathSum) {
    pathSum += node->score;

    // Leaf node -> print sum of scores along root-to-leaf path
    if (node->children.empty()) {
        cout << pathSum << '\n';
        return;
    }

    for (auto& [name, child] : node->children) {
        dfs(child, pathSum);
    }
}

int main() {

    /*
        Example:

        mail.test.mydomain.com -> 20
        www.test.com           -> -5
        mail.test.com          -> 10

        Tree:

                         com
                          |
                        test
                       /    \
                    mail    www
                      |
                   mydomain

        Scores:

        mail.test.com          -> 10
        mail.test.mydomain.com -> 20
        www.test.com           -> -5

        Path sums:

        com -> test -> mail -> mydomain
        = 0 + 0 + 10 + 20
        = 30

        com -> test -> www
        = 0 + 0 - 5
        = -5

        Output:
        30
        -5
    */

    vector<pair<string, int>> domains = {
        {"mail.test.mydomain.com", 20},
        {"www.test.com", -5},
        {"mail.test.com", 10}
    };

    Node* root = new Node();

    // Build the domain tree.
    // Reverse each domain so that "com" becomes the root.
    for (auto& [domain, score] : domains) {

        vector<string> parts = split(domain);
        reverse(parts.begin(), parts.end());

        Node* curr = root;

        for (const string& part : parts) {

            if (!curr->children.count(part)) {
                curr->children[part] = new Node();
            }

            curr = curr->children[part];
        }

        // Score belongs to this complete domain.
        curr->score = score;
    }

    // Start DFS with path sum = 0.
    dfs(root, 0);

    /*
        TC:
        Let N = total number of domain components across all input domains.

        Building tree: O(N) average
        DFS:            O(N)
        Overall:        O(N) average

        SC:
        Tree stores O(N) nodes.
        DFS recursion can take O(H), where H is maximum domain depth.

        Overall auxiliary/total space: O(N)
    */
}