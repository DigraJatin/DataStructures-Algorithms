// english dictionary
// a, b, c, d ........ xyz

// alien dictionary ordering we need to find

// Given lexographically ordered string, determine from them.
// baa, abcd, abca, cab, cad - not standard order

// lexographically order below
// cab
// cad
// first position they differ is index 2, so b < d in order confirmed
// this rule forms a directed graph
// chars = nodes, comes before = directed edge (b->d)
// if we can just do a topo sort we get the ordering

// edge case w1,w2 ordered
// w1.size() > w2.size() && w2 = prefix(w1) -> not possible return ""

string getDictionaryOrder(vector<string>& words){
	// build a graph with unique chars
	unordered_map<char, unordered_set<char>> adj;
	unordered_map<char, int> inDegree;
	// init graph
	for(auto &word : words){
		for(char c : word){
			adj[c] = unordered_set<char>{};
			inDegree[c] = 0;
		}
	}

	// iterate over adjacent words
	for(int i = 1; i < words.size(); i++){
		string w1 = words[i-1], w2 = words[i];
		int minLen = min(w1.size(), w2.size());

		if(w1.size() > w2.size() && w1.substr(0, minLen) == w2.substr(0, minLen)){
			return ""; // wrong
		}

		for(int j = 0; j < minLen; j++){
			if(w1[j] != w2[j]){
				if(!adj[w1[j]].count(w2[j])){ // not already present in adj list
					adj[w1[j]].insert(w2[j]);
					inDegree[w2[j]]++;
				}
				break;
			}
		}
	}

	// just to topo sort using bfs (kahn algo) and return the order
	queue<char> q;
	for(auto &[c, deg] : inDegree){
		if(deg == 0) q.push(c);
	}

	string res;
	while(!q.empty()){
		char curr = q.front();
		q.pop();
		res += curr;

		for(auto nei : adj[curr]){
			inDegree[nei]--;
			if(inDegree[nei] == 0){
				q.push(nei);
			}
		}
	}

	return res.size() == inDegree.size() ? res : "";
}

// TC O(N + V + E)
// SC O(V + E) - we built the adj ourself
