// Given A,B,C sorted arrays and D 

// Find count of tuples where these conditions satisfy 

// 1. Abs(A[i] - B[j]) <= D 
// 2. Abs(A[i] - C[k]) <= D 
// 3. Abs(B[j] - C[k]) <= D

long long solve(vector<int>& a, vector<int>& b, vector<int>& c, int d){
	long long ans = 0;
	vector<pair<int, char>> arr = merge(a, b, c);

	// for(int x : A) arr.push_back({x, 'A'});
	// for(int x : B) arr.push_back({x, 'B'});
	// for(int x : C) arr.push_back({x, 'C'});	

	// sort(arr.begin(), arr.end()); // can be merged in O(N) as well
	
	// count of A elements, B elements, C elements in the window
	vector<int> count(3, 0);

	int l = 0;
	// arr[r] - arr[l] <= D
	for(int r = 0; r < arr.size(); r++){
		count[arr[r].second - 'A']++;

		// shrink the window
		while(arr[r].first - arr[l].first > D){
			count[arr[l].second - 'A']--;
			l++;
		}

		// now we have a window satisfying the distance problem
		// arr[r] is the right most element
		int type = arr[r].second;
		if(type == 'A'){
			ans += 1LL* count['B'-'A'] * count['C'-'A'];
		} else if(type == 'B'){
			ans += 1LL* count['C'-'A'] * count['A'-'A'];
		} else {
			ans += 1LL* count['B'-'A'] * count['A'-'A'];
		}
	}

	return ans;
}

vector<pair<int, int>> merge(
    vector<int>& A,
    vector<int>& B,
    vector<int>& C
) {
    int i = 0, j = 0, k = 0;

    vector<pair<int, int>> res;

    while (i < A.size() || j < B.size() || k < C.size()) {

        int val = INT_MAX;
        int type = -1;

        if (i < A.size() && A[i] < val) {
            val = A[i];
            type = 0;
        }

        if (j < B.size() && B[j] < val) {
            val = B[j];
            type = 1;
        }

        if (k < C.size() && C[k] < val) {
            val = C[k];
            type = 2;
        }

        res.push_back({val, type});

        if (type == 0) i++;
        else if (type == 1) j++;
        else k++;
    }

    return res;
}