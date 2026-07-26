// Implement a function that, given a collection of words and a query prefix, returns all words that start with the given prefix.

// Example:

// words = ["abc", "abd", "abef", "xyz"]
// prefix = "ab"

// Output:

// ["abc", "abd", "abef"]

// N = number of words
// L = average word length
// M = length of the query prefix
// K = number of matching words returned

// | Metric           | Sort + Binary Search              | Trie               |
// | ---------------- | --------------------------------- | ------------------ |
// | **Build Time**   | `O(N log N × L)`                  | `O(N × L)`         |
// | **Single Query** | `O(log N + K × M)`                | `O(M + K)`         |
// | **Total Time**   | `O(N log N × L + log N + K × L)`  | `O(N × L + M + K)` |
// | **Extra Space**  | `O(1)` (or `O(log N)` sort stack) | `O(N × L)`         |

// sorting solution
vector<string> solveSorting(vector<string>& words, string& prefix){
	sort(words.begin(), words.end());
	auto it = lower_bound(words.begin(), words.end(), prefix);

	vector<string> ans;

	while(it != words.end()){
		if(it->compare(0, prefix.size(), prefix) != 0) break;
		ans.push_back(*it);
		++it;
	}

	return ans;
}

// Trie solution

struct TrieNode {
	TrieNode* children[26];
	bool isEnd;

	TrieNode() {
		isEnd = false;
		for(int i = 0; i < 26; i++) children[i] = nullptr;
	}
};


class Trie {
	TrieNode* root;

	void dfs(TrieNode* node, vector<string>& retVal, string& curr){
		if(node->isEnd) retVal.push_back(curr); // no return because is end means a word ends here not that any
		// word no longer exists

		for(int i = 0; i < 26; i++){
			if(node->children[i]){
				curr.push_back('a' + i);
				dfs(node->children[i], retVal, curr);
				curr.pop_back();
			}
		}
	}

public :
	Trie() {
		root = new TrieNode();
	}

	void insert(string& word){
		TrieNode* node = root;
		for(char c : word){
			int idx = c - 'a';
			if(!node->children[idx]){
				node->children[idx] = new TrieNode();
			}
			node = node->children[idx];
		}
		node->isEnd = true;
	}

	vector<string> searchPrefix(string& prefix){
		TrieNode* node = root;
		for(char c : prefix){
			int idx = c - 'a';
			if(!node->children[idx]) return {};
			node = node->children[idx];
		}

		vector<string> ans;
		string curr = prefix;
		dfs(node, ans, curr);
		return ans;
	}
};