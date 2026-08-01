// Given logs when people enter and leave
// return who was there at each interval

// input:

// name | start_time | end_time
// Abby         10        100
// Ben          50        70
// Carla        60        90
// Bob          110       120
// output:

// start_time | end_time | names
//    10           50       Abby
//    50           60       Abby, Ben, Carla
//    60           70       Abby, Ben, Carla
//    70           90       Abby, Carla
//    90           100      Abby
//    110          120      Bob
// Clarifications:

// Dont output empty intervals (no people)
// Multiple people can enter or leave at same time

struct Log {
	string name;
	int start;
	int end;
};

struct Event {
	string name;
	bool enter; // true = enter, false = leaving
	int time;
};


struct CompSort {
	bool operator()(const Event& a, const Event& b){
		return a.time < b.time;
	}
};

vector<tuple<int, int, vector<string>>> solve(vector<Log>& logs){

    vector<Event> events;
	// Create events
	for (auto& log : logs) {
		events.push_back({log.name, true, log.start});
		events.push_back({log.name, false, log.end});
	}
	sort(events.begin(), events.end(), CompSort()); // sort by time of occurence 

	// set keeps names in lexo order
	set<string> active;
	vector<tuple<int, int, vector<string>>> ans;

	int i = 0;
	while(i < events.size()){
		int currTime = events[i].time;
		// handle multiple events happening at same time
		while(i < events.size() && currTime == events[i].time){
			if(events[i].enter) active.insert(events[i].name);
			else active.erase(events[i].name);
			i++;
		}

		if(i == events.size()) break;

		int nextTime = events[i].time;
		if(!active.empty()){
			ans.push_back({currTime, nextTime, vector<string>(active.begin(), active.end())});
		}
	}

	return ans;
}

// TC: O(N log N)
// - 2N events
// - Sorting: O(N log N)
// - Each insert/erase: O(log N)
//
// SC: O(N)