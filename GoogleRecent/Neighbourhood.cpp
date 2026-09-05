vector<vector<int>> rearrangeHouse(const vector<vector<int>>& houses){
	int n = houses.size(); // no of neighbourhoods
	vector<vector<int>> result;
	if(n == 0) return result;
	else result.resize(n);

	vector<int> cap(n);
	unordered_map<int, int> fq;

	for(int i = 0; i < n; i++){
		cap[i] = houses[i].size();
		for(int x : houses[i]){
			fq[x]++;
			if(fq[x] > n) return res;
		}
	}

	// freq-houseid max heap
	priority_queue<pair<int,int>> pq;
	for(auto &[h, f] : fq) pq.push({f, h});

	// capacity available - house id max heap
	priority_queue<pair<int,int>> housePQ;
	for(int i = 0; i < n; i++){
		if(cap[i] > 0) pq.push({cap[i], i});
	}

	// assign house with highest frequency to house with highest capacity
	while(!pq.empty()){
		auto [f, h] = pq.top();
		pq.pop();

		// we need to pick unique houses from housePQ
		// so we pop but don't push immediately
		vector<pair<int,int>> used;
		for(int int i = 0; i < f; i++){
			if(housePQ.empty()){
				result.clear();
				return result;
			}

			auto [cap, idx] = housePQ.top();
			housePQ.pop();

			result[idx].push_back(h);
			cap--;
			used.push_back({cap, idx});
		}

		// insert again
		for(auto &[cap, idx] : used){
			if(cap > 0) housePQ.push({cap, idx});
		}
	}

	for(auto &row : result) sort(row.begin(), row.end());
	return result; 
}