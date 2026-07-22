/* Given an origin airport, destination airport, and series of flights determine whether it is possible for a package at the origin to reach the destination. 
A flight is represented as departure airport, arrival airport, departure time, and arrival time.
During the transportation, the time that the package leaves the airport needs to be greater than or equal to the time it arrives at the airport. 
Please determine whether it is possible for a package transfer from s to t. The package arrived at s at time 0. 

Follow ups :
1. Checking if reachable or not - normal BFS or DFS can work (this is without time constraings)
2. Above problem with time constraints - normal BFS / DFS with visited does not work because state is now (airpot, arrivalTime)
3. To check if reachable we can use SPFA/Bellman ford
4. To get the minimum time to reach destination we need to use Dijkstra
*/

/*
E.g. 1
Origin: "NYC"
Destination: "SFO"
Flights: NYC → LAX, Departure: 0, Arrival: 4
LAX - SFO, Departure: 5, Arrival: 7
Output: True

E.g 2
Origin: "NYC" Destination: "SFO"
Flights: NYC →> LAX, Departure: 0, Arrival: 4
LAX -> SFO, Departure: 3, Arrival: 5
Output: False 
*/

#include <iostream>

using namespace std;

struct Flight {
	string from;
	string to;
	int arrival; // belongs to from
	int departure; // belongs to arrival
};

int main() {
	// flight = (from, to, departureTime, arrivalTime)
	// NYC -> LAX, Departure = 2, Arrival = 5
	// Flight leaves NYC at 2, arrives at LAX at 5
	// We can take this flight if arrival[NYC] <= Departure(2)

	// Curr-----Next (Flight) possible if
	// flight.departure >= arrivalAtCurr

	// after flight
	// newAirpot = Flight.to
	// newTime = Flight.arrival

	// normal dijkstra (node, distance)
	// here (airport, arrivalTime) - earlier the arrival time (smaller value is better)

	vector<Flight> flights; // fill the data from example
	string source, destination;

	int timeAns = minimumTimeDijkstra(flights, source, destination);
	
	return 0;
}


// Dijkstra algorithm
// TC O((V+E))logV)
// SC O(V+E)

// single source to all nodes

/* 												//  {v, w}		
vector<int> dijkstra(int source, vector<vector<pair<int,int>>>& adj, int N){
	vector<int> dist(n, INT_MAX);
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

	pq.push({0, src});
	dist[src] = 0;

	while(!pq.empty()){
		auto top = pq.top();
		pq.pop();

		int u = top.second;
		int d = top.first;

		if(d > dist[u]) continue;

		for(auto nei : adj[u]){
			int v = nei.first;
			int wt = nei.second;

			if(dist[u] + wt < dist[v]){
				dist[v] = dist[u] + wt;
				pq.push({dist[v], v});
			}
		}
	}

	return dist;
}
*/

int minimumTimeDijkstra(vector<Flight> flights, string src, string dst){
	// adj list
	unordered_map<string, vector<Flight>> adj;
	for(auto flight : flights){
		adj[flight.from].push_back(flight);
	}

	// dist array using map
	unordered_map<string, int> earliestArrival;
	for (auto &flight : flights) {
	    earliestArrival[flight.from] = INT_MAX;
	    earliestArrival[flight.to] = INT_MAX;
	}

	// state is (arrivalTime, airport)
	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int,string>>> pq;
	pq.push({0, src});
	earliestArrival[src] = 0;

	while(!pq.empty()){
		auto [currTime, airport] = pq.top();
		pq.pop();

		if(currTime > earliestArrival[airport]) continue;

		if(airport == dst) return currTime;

		for(auto &flight : adj[airport]){
			// can we board additional condition rest is just standard dijkstra
			if(flight.departure >= currTime && flight.arrival < earliestArrival[flight.to]){
				earliestArrival[flight.to] = flight.arrival;
				pq.push({flight.arrival, flight.to});
			}
		}
	}

	if(earliestArrival[dst] == INT_MAX) return -1;
	return earliestArrival[dst];
}

// BellMan Ford algorithm
// TC O(VE)
// SC O(V)

// single source to all nodes
// doing 1 extra pass after V-1 helps detect negative cycles in graph

/* 												//  {v, w}		
vector<int> bellman(int source, vector<vector<pair<int,int>>>& adj, int N){
	vector<int> dist(n, INT_MAX);
	dist[src] = 0;
	
	// in place bellmand ford with storing previous pass result
	for(int i = 1; i <= N - 1; i++){
		for(const auto &edge : adj){
			if(dist[edge.u] == INT_MAX) continue; // means i have not yet found dist for this node

			if(dist[edge.u] + edge.wt < dist[edge.v]){
				dist[edge.v] = dist[edge.u] + wt;
			}
		}
	}

	// prev variant, use when at most K edges variant
	for(int i = 1; i <= N - 1; i++){
		vector<int> prev = dist;
		for(auto &edge : edges){
			if(prev[edge.u] == INT_MAX) continue;

			if(prev[edge.u] + edge.wt < dist[edge.v]) {
				dist[edge.v] = prev[edge.u] + edge.wt;
			}
		}
	}

	return dist;
}
*/

int minimumTimeBellmanFord(vector<Flight> flights, string src, string dst) {

    // Earliest arrival time at each airport
    unordered_map<string, int> earliestArrival;

    for (const auto &flight : flights) {
        earliestArrival[flight.from] = INT_MAX;
        earliestArrival[flight.to] = INT_MAX;
    }

    earliestArrival[src] = 0;

    int V = earliestArrival.size();

    // V-1 relaxation passes
    for (int pass = 1; pass <= V - 1; pass++) {

        bool changed = false;

        for (const auto &flight : flights) {

            // Can't reach source airport yet
            if (earliestArrival[flight.from] == INT_MAX)
                continue;

            // Can't board this flight
            if (flight.departure < earliestArrival[flight.from])
                continue;

            // Relax
            if (flight.arrival < earliestArrival[flight.to]) {
                earliestArrival[flight.to] = flight.arrival;
                changed = true;
            }
        }

        // Nothing changed, answer has converged
        if (!changed)
            break;
    }

    return earliestArrival[dst] == INT_MAX ? -1 : earliestArrival[dst];
}