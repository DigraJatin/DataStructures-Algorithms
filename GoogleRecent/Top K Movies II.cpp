/* Given N Movies similar like Part 1
but priority is - smaller distance, higher rating, smaller id
Skip already watched movies and src movie */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> solution(vector<vector<int>>& adj, vector<int>& rating, int start, vector<int>& watched, int k) {
    	int N = rating.size();
    	vector<bool> visited(N, false);
    	queue<int> q;

    	unordered_set<int> skip;
    	for(auto  i : watched) skip.insert(i);

    	q.push(start);
    	visited[start] = true;
		skip.insert(start);
    	vector<int> result;

    	while(!q.empty()){
    		int levelSize = q.size();
    		vector<int> temp;
    		for(int i = 0; i < levelSize; i++){
    			int curr = q.front();
    			q.pop();

    			if(skip.find(curr) == skip.end()) temp.push_back(curr);
    			for(auto &nei : adj[curr]){
    				if(visited[nei]) continue;
    				q.push(nei);
    				visited[nei] = true;
    			}
    		}

    		sort(temp.begin(), temp.end(), comp(rating));
    		for(auto i : temp){
    			result.push_back(i);
    			if(result.size() == k) return result;
    		}
    	}

    	return result;
    }

private :
	struct comp {
		vector<int> ratings;
		
		comp(vector<int>& _ratings) : ratings(_ratings) {}

		bool operator()(int a, int b){
			if(ratings[a] != ratings[b]) return ratings[a] > ratings[b];
			return a < b;
		}
	};
};

int main() {
	/*
		adj     = [[1, 2], [0, 3], [0, 3, 4], [1, 2], [2]]
		rating  = [5, 7, 6, 9, 8]
		start   = 0
		watched = [0, 2]
		k       = 3
		=> [1, 3, 4] 
	*/
	int N = 5;
	int k = 3;
	int start = 0;
	vector<int> rating = {5, 7, 6 ,9, 8};
	vector<int> watched = {0, 2};
	vector<vector<int>> adj(N);
	adj[0] = {1, 2};
	adj[1] = {0, 3};
	adj[2] = {0, 3, 4};
	adj[3] = {1, 2};
	adj[4] = {2};
    
    Solution obj;
	auto ans = obj.solution(adj, rating, start, watched, k);
	for(auto i : ans) cout << i << " ";
	cout << endl;
	return 0;
}

/*
=== Top K Movies - Part 2 ===
Approach: BFS (level-by-level) + Sort per level
- BFS explores all reachable movies from start, processing one level (distance) at a time.
- At each level, collect all eligible movies (not in watched, not start) into a temp vector.
- Sort temp by (higher rating first, smaller ID breaks ties).
- Append sorted movies to result; stop early once result.size() == K.
- Key: must finish collecting the entire level before sorting, since all movies at the same
  distance compete equally and we need the best among them.

Ranking: smaller distance first, higher rating second, smaller ID third.

TC: O(V + E + V*logV)
  - BFS visits every node and edge once: O(V + E)
  - Sorting across all levels: sum of sort costs per level. In the worst case all V nodes
    are at the same level -> one sort of V elements: O(V * logV).
    Across levels, total sorted elements <= V, so total sort cost is O(V * logV).
  - Building the watched set: O(W) where W = watched.size()
  - Total: O(V + E + V*logV)

SC: O(V + W)
  - O(V) for visited array, BFS queue, result vector, temp vectors (reused per level)
  - O(W) for the skip (watched) unordered_set
  - Total: O(V + W)
*/