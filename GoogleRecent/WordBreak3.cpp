// Construct the word from dic with shortest no
// of words needed

int n;
vector<string> nextWord;

// returns the minimum number of words required
// storing answer in nextWord
int dfs(int idx, string s, vector<string> dict){
	if(idx == n) return 0;

	int best = INT_MAX;

	for(auto w : dict){
		if(w == s.substr(idx, w.size())){
			int subProblemCount = dfs(idx + w.size(), s, dict);
			if(subProblemCount != INT_MAX){
				if(1 + subProblemCount < best){
					best = 1 + subProblemCount;
					// so from index idx we can use word w
					nextWord[idx] = w;
				}
			}
		}
	}

	return best;
}

vector<string> solve(string s, vector<string>& words){
	n = s.size();

	if(dfs(0, s, words) == INT_MAX) return {};

	// nextWord basically contains the final answer
	// word1 "" "" "" word2 .... like this
	// at every index where a new word starts it has the word

	vector<string> ans;
	for(int idx = 0; idx < n;){
		ans.push_back(nextWord[idx]);
		idx += nextWord[idx].size();
	}

	return ans;
}