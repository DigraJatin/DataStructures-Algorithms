/* Given N movies and movies of same genre are connected, each movie has a rating and ID,
for a movie src, return top K rated movies similar to it, if 2 movies have same rating, higher ID wins */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public :
	
	struct Movie {
		int rating;
		int id;
	};

	vector<int> getTopKSimilarMovies(const vector<Movie>& movies, const vector<vector<int>>& adj, int src, int k){
		int N = movies.size() - 1; // 1 based indexing used, idx 0 is unused
		vector<int> result;
		if(src < 1 || src > N || k <= 0) return result;

		vector<bool> visited(N+1, false);
		queue<int> q;
		priority_queue<Movie, vector<Movie>, Compare> pq;

		q.push(src);
		visited[src] = true;
		while(!q.empty()){
			int curr = q.front();
			q.pop();

			for(int neighbour : adj[curr]){
				if(visited[neighbour]) continue;
				
				visited[neighbour] = true;
				q.push(neighbour);

				Movie candidate = movies[neighbour];
				if(pq.size() < k){
					pq.push(candidate);
					continue;
				}

				Movie worst = pq.top();
				if(candidate.rating > worst.rating || (candidate.rating == worst.rating && candidate.id > worst.id)){
					pq.pop();
					pq.push(candidate);
				}
			}
		}

		while(!pq.empty()){
			result.push_back(pq.top().id);
			pq.pop();
		}

		reverse(result.begin(), result.end());
		return result;
	}

private :
	/* min heap has syntax priority_queue<int, vector<int>, greater<int>> minHeap,
	but we need to overload() for our struct Movie */
	struct Compare {
		bool operator()(const Movie&a, const Movie& b) const {
			// min heap -> smaller values on top, smaller values have more priority
			// does a have a lower priority than b, Yes -> Swap places
			if(a.rating != b.rating) return a.rating > b.rating;
			return a.id > b.id ;
		} 
	};
};

int main() {
	int N = 6;
	vector<Solution::Movie> movies(N + 1);
	movies[1] = {5, 1};
	movies[2] = {3, 2};
	movies[3] = {4, 3};
	movies[4] = {5, 4};
	movies[5] = {2, 5};
	movies[6] = {4, 6};

	vector<vector<int>> adj(N+1);
	adj[1] = {2, 3};
	adj[2] = {1, 4, 5};
	adj[3] = {1, 4, 6};
	adj[4] = {2, 3, 6};
	adj[5] = {2};
	adj[6] = {3, 4};

	Solution solve;
	vector<int> ans = solve.getTopKSimilarMovies(movies, adj, 2, 3);
	// print ans
	for (int id : ans) cout << id << " ";
	cout << endl;
	return 0;
}

/*
=== Top K Movies - Part 1 ===
Approach: BFS + Min-Heap of size K
- BFS explores all reachable movies from src (all same-genre movies).
- Min-heap of size K keeps the top K rated movies seen so far.
- For each new movie: if heap size < K, push it; else compare with heap top (worst of the K best)
  and replace if the new movie is better.
- At the end, pop all K from heap and reverse for descending order.

Ranking: higher rating first, higher ID breaks ties.

TC: O(V + E + V*logK)
  - BFS visits every node and edge once: O(V + E)
  - Each of the V nodes does at most one push/pop on a size-K heap: O(V * logK)
  - Final extraction from heap: O(K * logK)
  - Total: O(V + E + V*logK)

SC: O(V + E)
  - O(V) for visited array, BFS queue (at most V nodes), result vector
  - O(K) for the min-heap (K <= V)
  - O(E) for adjacency list (input, not extra but counted for completeness)
  - Total: O(V + E)
*/
