// Design a data structure that receives

// (timestamp, item)

// and returns whether the item is a duplicate within the last 60 seconds.

// Requirements

// O(1) average lookup
// O(1) amortized cleanup
// Automatically remove expired entries


class Deduplicator {
public :
	Deduplicator(long long ttlSeconds = 60){
		window = ttlSeconds; // how long the item stays
	}

	// return true if duplicate else false
	bool process(Event& event){
		cleanUp(event.timeStamp);
		bool duplicate = lastSeen.count(event.item);
		lastSeen[event.item] = event.timeStamp;
		q.push(event);
		return duplicate;
	}

private :
	
	struct Event {
		long long timeStamp;
		string item;
	};

	long long window;
	// latest timestamp of every active item
	unordered_map<string, long long> lastSeen;
	queue<Event> q; // FIFO arrival order

	void cleanUp(long long currentTime){
		while(!q.empty() && currentTime - q.front().timeStamp >= window){
			auto event = q.front();
			q.pop();

			// erase only if this queue entry is still latest occurence of this item
			if(lastSeen[event.item] == event.timeStamp){
				lastSeen.erase(event.item);
			}
		}
	}
};