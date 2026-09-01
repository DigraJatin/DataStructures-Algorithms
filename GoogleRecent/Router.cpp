struct Router {
	string name;
	int x, y;
};

double distance (const Router& a, const Router& b){
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}

int main() {

    vector<Router> routers = {
        {"A",0,0},
        {"B",0,8},
        {"C",0,17},
        {"D",11,0}
    };

    double range = 10;

    cout << (canReach(routers,0,3,range) ? "Reachable" : "Not Reachable")
         << endl;

    return 0;
}

// You are given a list of routers & their 2D location coordinates, a source router, a destination router, and a range value. Each router when receives a message, broadcasts it to other routers which are in range. Whenever a router broadcasts a message, it shuts-down permanently. Write an implementation for a method which determines whether a message starting from a source router is reachable to a destination router.

// For example, Router A is at (0, 0); Router B is at (0, 8); Router C is at (0, 17); Router D is at (11, 0). Range is 10.

// Src - A, Dest - D

// When Router A sends a message, it could first reach B; the message from Router B would further reach Router C but Router D would never receive this message.

// The distance between two routers are calculated using "Euclidean Distance".

// this code is for case when on collision the router breaks and can no longer transfer messages again

bool canReach(const vector<Router>& routers, int src, int dest, double range) {
    int n = routers.size();

    // Build graph
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (distance(routers[i], routers[j]) <= range) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    vector<bool> visited(n, false);
    queue<int> q;

    visited[src] = true;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == dest)
            return true;

        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return false;
}

// TC O(N² + V + E)
// SC O(V + E), WC O(N^2)

// Follow-up:
// Suppose we discard message collisions, how would you update your solution? For example, if router D is destination, 
// and it receives 2 or more messages at the same time, the message is considered to be collided and then discarded i.e. not reachable. 
// Only those messages are considered to be reachable which are not colliding with others at the same time.

// Assume time for a message to reach any router is proportional to the distance.

// edge = distance b/w routers
// use dijkstra
// dist[i] = shortest distance or time
// ways[i] = no of routes via dist[i]

struct Edge {
    int to;
    double wt;
};

bool canReachWithCollision(const vector<Router>& routers,
                           int src,
                           int dest,
                           double range) {

	const double INF = 1e18;
	const double EPS = 1e-9;

    int n = routers.size();

    vector<vector<Edge>> graph(n);

    // Build weighted graph
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = distance(routers[i], routers[j]);

            if (d <= range) {
                graph[i].push_back({j, d});
                graph[j].push_back({i, d});
            }
        }
    }

    vector<double> dist(n, INF);
    vector<int> ways(n, 0);

    priority_queue<pair<double,int>,
                   vector<pair<double,int>>,
                   greater<pair<double,int>>> pq;

    dist[src] = 0;
    ways[src] = 1;

    pq.push({0, src});

    while (!pq.empty()) {

        auto [currDist, u] = pq.top();
        pq.pop();

        if (currDist > dist[u] + EPS) // eps is written on lesser side <
            continue;

        // Collision occurred.
        // This router never forwards the message.
        if (ways[u] > 1)
            continue;

        for (auto &edge : graph[u]) {

            int v = edge.to;
            double newDist = dist[u] + edge.wt;

            // Strictly smaller
            if (newDist + EPS < dist[v]) {

                dist[v] = newDist;
                ways[v] = 1;

                pq.push({dist[v], v});
            }
            // Approximately equal
            else if (fabs(newDist - dist[v]) < EPS) {

                ways[v]++;

                // Push again so when popped we know it collided
                pq.push({dist[v], v});
            }
        }
    }

    return ways[dest] == 1;
}

// TC O(N² + (V + E) log V), dense graph E = O(N²), O(N² log N)
// SC O(V + E), WC O(N^2)



// What is EPS?
// const double EPS = 1e-9;

// It is a tiny tolerance.

// Instead of saying

// a == b

// we say

// fabs(a - b) < EPS

// meaning

// "The numbers differ by less than 10^−9 , so treat them as equal."


// What is fabs()?

// fabs() = floating-point absolute value.

// Examples:

// fabs(5 - 3);      // 2
// fabs(3 - 5);      // 2
// fabs(-2.7);       // 2.7

// So

// fabs(newDist - dist[v]) < EPS

// means

// |newDist - dist[v]| < 1e-9

// i.e., the two distances are effectively equal.

