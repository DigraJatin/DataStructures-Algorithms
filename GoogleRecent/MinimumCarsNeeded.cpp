// Given N cars and a list of rental requests (each with pickupTime, returnTime, and id), assign cars to maximize utilization while using the minimum number of cars possible. 

// Each car can serve multiple requests as long as they don't overlap in time. For example, if Request A returns at time 5 and Request B picks up at time 5, the same car can serve both requests.
// Input:
// N = 3 
// requests = [
//   {id: 1, pickup: 0, return: 5},
//   {id: 2, pickup: 2, return: 7},
//   {id: 3, pickup: 5, return: 9}
// ] 


// Output:
// [
//   {requestId: 1, carId: 0},
//   {requestId: 2, carId: 1},
//   {requestId: 3, carId: 0}
// }


#include <bits/stdc++.h>
using namespace std;

struct Request {
    int id;
    int pickup;
    int drop;
};

vector<pair<int,int>> assignCars(vector<Request>& requests, int N) {

    // Sort by pickup time
    sort(requests.begin(), requests.end(),
         [](const Request& a, const Request& b) {
             return a.pickup < b.pickup;
         });

    // Free car IDs
    priority_queue<int, vector<int>, greater<int>> availableCars;

    for (int i = 0; i < N; i++)
        availableCars.push(i);

    // (returnTime, carId)
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > busyCars;

    vector<pair<int,int>> ans;

    for (auto &req : requests) {

        // Release finished cars
        while (!busyCars.empty() &&
               busyCars.top().first <= req.pickup) {

            availableCars.push(busyCars.top().second);
            busyCars.pop();
        }

        if (availableCars.empty())
            throw runtime_error("Not enough cars");

        int car = availableCars.top();
        availableCars.pop();

        ans.push_back({req.id, car});

        busyCars.push({req.drop, car});
    }

    return ans;
}

// Let M = requests.size()

// Sorting        : O(M log M)
// Heap operations: O(M log N)

// TC: O(M log M)
// SC: O(N)