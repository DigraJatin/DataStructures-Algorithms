// determin duplicate present in [l,r] range query


vector<int> mx;

void preprocessing(vector<int>& nums){
	int n = nums.size();
	unordered_map<int, int> last;

	for(int i = 0; i < n; i++){
		int prev = -1;

		if(last.find(nums[i]) != last.end()){
			prev = last[nums[i]];
		}

		last[nums[i]] = i;

		if(i == 0) mx[i] = prev;
		else mx[i] = max(mx[i-1], prev);
	}
}

bool query(int l, int r){
	return mx[r] >= l;
}