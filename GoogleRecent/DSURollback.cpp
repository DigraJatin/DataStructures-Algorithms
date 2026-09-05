// Normal DSU works with path compression and rank union by rank/size to achieve O(alpha(n)) tc for unite, find operations
// useful for finding no of components or when all become connected, standard code

// But we have DSU rollback that supports rolling back the last added edge only, TC goes to O(log(n)) and we remove path compression,
// so it only works with union by rank size 

class DSURollback{
public :
	int components;
	vector<int> parent, rank;
	// u,v,rankChanged 
	stack<tuple<int,int,bool>> history;

	DSURollback(int n) : components(n) {
		parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
		rank.assign(n, 0);
	}

	int find(int x){
		while(parent[x] != x) x = parent[x]; // no path compression here, normal dsu does return parent[x] = find(parent[x]);
		return x;
	}

	void unite(int u, int v){
		int pu = find(u), pv = find(v);

		if(pu == pv){
			// already connected
			history.push({-1,-1, false}); // marker for no operation happened
			return;
		}

		bool rankChanged = (rank[pu] == rank[pv]);
		// we want to link pv under pu always
		if(rank[pu] < rank[pv]) swap(pu, pv);
		parent[pv] = pu;
		if(rankChanged) rank[pu]++;

		// we push parents remember
		history.push({pu,pv, rankChanged});
		components--;
	}

	void rollback(){
		auto [u, v, rankChanged] = history.top();
		history.pop();
		if(u == -1) return; // no op, no affect
		parent[v] = v; // revert parent change
		if(rankChanged) rank[u]--;
		components++;
	}
};

// Operation	Time
// find	O(log n)
// unite	O(log n)
// rollback	O(1)
// Space	O(n) for parent/rnk + O(q) for the history stack

// We have timestamps in order
// But now we also need to deal with disconnect requests
// Find earliest time everyone becomes connected

// dsu rollback is used from above

class SegmentTree {
    // tree[node] = all edges that are active
    // for the ENTIRE interval represented by this node
    vector<vector<pair<int, int>>> tree;
    int T;

    SegmentTree(int n) {
	    T = n;
	    // 4*T is enough for a normal segment tree
	    tree.resize(4 * n);
	}

	// add edge u-v, to every time in ql, qr
	void addEdge(int node, int l, int r, int ql, int qr, int u, int v){
		if(qr < l || ql > r) return;
		if(ql <= l && qr >= r) {
			// full pverlap
			tree[node].push_back({u,v});
			return;
		}
	}

	int mid = (l + r)/2;
	addEdge(2*node, l, mid, ql, qr, u, v);
	addEdge(2*node + 1, mid + 1, r, ql, qr, u, v);

	// wrapper
	void addEdge(int l, int r, int u, int v){
		if(l > r) return;
		addEdge(1, 0, T-1, l, r, u, v);
	}

	// dfs on the tree doing dsu
	void process(int node, int l, int r, DSURollback& dsu, vector<int>& answer){
		int edgesAdded = 0;
		// all edges from current node
		for(auto &[u,v] : tree[node]){
			dsu.unite(u, v);
			edgesAdded++;
		}

		// if leaf this represent no of components at leaft time
		if(l == r) answer[l] = dsu.components;
		else {
			int mid = (l + r)/2;
			process(2*node, l, mid, dsu, answer);
			process(2*node + 1, mid + 1, r, dsu, answer);
		}

		// rollback edges added
		while(edgesAdded--){
			dsu.rollback();
		}
	}

	// wrapper
	void process(DSURollback& dsu, vector<int>& ans){
		process(1, 0, T-1, dsu, answer);
	}
};

// convert logs to time

struct Log { 
	int type;  // type: 0=add, 1=remove
	int u, v; 
	long long timestamp; 
};

long long solve(int n, vector<Log>& logs){
    int T = logs.size(); // no of logs
    if (T == 0) return (n <= 1) ? 0 : -1;

    // n = no of nodes/individual people
    SegmentTree st(T);	
    DSURollback dsu(n); 

    // Map to store the log index when an edge was added.
    // can use unordered map but need to provied hasher
    // std::map has inbuild hash support for pair<int,int>
    map<pair<int, int>, int> active_edges;
    // Key: {u, v} ensuring u < v, Value: index in logs array
    for (int i = 0; i < T; i++) {
    	int u = logs[i].u;
        int v = logs[i].v;
        if (u > v) swap(u, v); // Normalize to ensure consistency

        if (logs[i].type == 0) {
        	// add edge
        	active_edges[{u, v}] = i; // we store the version of graph
        } else {
        	// Remove edge
        	if (active_edges.count({u, v})) {
                int start_time_idx = active_edges[{u, v}];
                // The edge was active from the time it was added until just before it was removed.
                // called segment tree add
                st.addEdge(start_time_idx, i - 1, u, v);
                active_edges.erase({u, v});
            }
        }
    }

    // Any edge still active remains active until the very last log.
    for (auto& [edge, start_time_idx] : active_edges) {
        st.addEdge(start_time_idx, T - 1, edge.first, edge.second);
    }

    vector<int> answer(T);
    st.process(dsu, answer);

    // Iterate through time to find the earliest point where everything is connected
    for (int i = 0; i < T; i++) {
        if (answer[i] == 1) {
            return logs[i].timestamp; // actual timestamp used
        }
    }

    return -1; // Never became fully connected
}



// You hit on a very subtle and brilliant detail of this algorithm.

// You are asking: "Why does storing an edge's lifespan as [start_index, end_index] work, when its actual life happened between [start_timestamp, end_timestamp]?"

// Here is the exact reason: We are not tracking "time." We are tracking "versions of the graph."

// Every time a log occurs, a new "version" of the graph is created.

// Index 0 represents Version 0 of the graph (which exists from time 10 to 14).

// Index 1 represents Version 1 of the graph (which exists from time 15 to 19).

// Index 2 represents Version 2 of the graph (which exists from time 20 onwards).

// If an edge is added at log 0 (time 10) and removed at log 2 (time 20), it exists in Version 0

// TC 
// logs processing using map T logs, O(log T) for one TLog(T)
// Segment tree node add - at most T nodes added - 1 addition = O(logT) = O(TLogT)
// DFS + DSU
// Total edges in seg tree across full tree= TLogT
// every edge was placed into at most O(logT) nodes
// DSU is O(log N)
// O(TlogTlogN)