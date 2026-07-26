// Buddy Pairs of Strings
// Problem Statement

// You are given a list of unique, non-empty strings consisting only of lowercase English letters.

// Two strings A and B are called buddy pairs if:

// They have the same length.
// For every adjacent pair of characters, the forward circular distance is the same in both strings.

// The forward circular distance from character x to y is defined as:

// (y - x + 26) % 26

// For example:

// dist('b', 'e') = 3
// dist('e', 'b') = 23

// Return the total number of buddy pairs in the list.

// Examples
// Input:
// ["abc", "def", "xyz", "az", "ba"]

// Output:
// 3

// Explanation:
// "abc", "def", and "xyz" have the same gap pattern [1,1], so they form:
// (abc, def)
// (abc, xyz)
// (def, xyz)

int solve(vector<string>& words){
	unordered_map<string, int> freq;
	int ans = 0;
	for(auto &w : words){
		string signature;
		for(int i = 0; i < w.size()-1; i++){
			signature += to_string((w[i+1] - w[i] + 26) % 26);
			signature += '%';
		}

		ans += freq[signature];
		freq[signature]++;
	}
	return ans;
}

// O(N*L) both TC and SC