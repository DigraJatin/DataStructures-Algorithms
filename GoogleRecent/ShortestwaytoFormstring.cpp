// LeetCode — Shortest Way to Form String

// Problem:
// Given two strings source and target, return the minimum number of subsequences of source needed to form target.

// A subsequence can be formed by deleting some characters from source without changing the order of the remaining characters.

// If it's impossible, return -1.

// Input:
// source = "xyz"
// target = "xzyxz"

// Output:
// 3

// Explanation:
// "xy" + "z" + "yxz" → "xzyxz"

// idea = Repeatedly find the longest prefix of the remaining target that can be matched as a subsequence of source.

int solve(string src, string target){
	if (target.empty()) return 0; // edge case
	bool src[26] = {false};
	for(char c : src){
		src[c-'a'] = true;
	}

	for(char c : target){
		if(src[c-'a'] == false) return -1;
	}

	int m = src.size();
	int n = target.size();

	int cnt = 1;
	int srcIterator = 0;

	for(char c : target){
		if(srcIterator == src.size()){
			cnt++;
			srcIterator = 0;
		}

		while(src[srcIterator] != c){
			srcIterator++;
			if(srcIterator == src.size()){
				cnt++;
				srcIterator = 0;
			}
		}

		srcIterator++;
	}

	// M = len of src, N = len of Target
	// O(M*N) TC WC (a, aaaaaaa)
	// O(M*K) TC Avg, where K = CNT
	return cnt;
}

// greedy linear works but we are searching for chars again and again in linear fashion
// can be improved

// for every char store indexes it's present at in increasing order
// SC - O(M)
// TC - O(M + NLogM)
int solve(string src, string target){
	vector<vector<int>> charToIndices(26);
	for(int i = 0; i < src.size(); i++){
		charToIndices[src[i]-'a'].push_back(i);
	}

	int srcIterator = 0;
	int count = 1;

	for(int i = 0; i < target.size(); i++){
		if(charToIndices[target[i] - 'a'].size() == 0) return -1;

		vector<int> indices = charToIndices[target[i] - 'a'];
		int index = lower_bound(indices.begin(), indices.end(), srcIterator) - indices.begin();
		if(index == indices.size()){
			count++;
			srcIterator = indices[0] + 1;
		} else {
			srcIterator = indices[index] + 1;
		}

	}

	return count;
}

//                       
// 2d precompute nextOccurrence[idx][char]
// nextOccurrence[i][c] gives the index of the next occurrence of character c 
// at or after position i in source
// constant lookup instead of binary search
// O(M + N)

int solve(string src, string target){
	int m = src.size(), n = target.size();
	int nextOccurrence[m][26];


	for(int c = 0; c < 26; c++){
		nextOccurrence[m-1][c] = -1; // at last index all chars are missing execpt last one
	}
	// for last char next occurence is last index
	nextOccurrence[m-1][src[m-1]-'a'] = m-1;

    // Fill using recurrence relation
    // The recurrence comes from this observation:
	// nextOccurrence[idx][c] = first occurrence of character c at or after index idx.
	// If src[idx] == c, answer is idx; otherwise, the first occurrence is the same as from idx+1.

	// already filled for m - 1
    for (int idx = m - 2; idx >= 0; idx--) {
        for (int c = 0; c < 26; c++) {
            nextOccurrence[idx][c] = nextOccurrence[idx + 1][c];
        }
        nextOccurrence[idx][source[idx] - 'a'] = idx;
    }

    int srcIterator = 0;
    int count = 1;
    for(char c : target){
    	// not present in source at all
    	if(nextOccurrence[0][c - 'a'] == -1){
    		return -1;
    	}

    	// reached end or not present after or at srcIterator
    	if(srcIterator == m || nextOccurrence[srcIterator][c - 'a'] == -1){
    		count++;
    		srcIterator = 0;
    	}

    	srcIterator = nextOccurrence[srcIterator][c-'a'] + 1;
    }

    return count;
}