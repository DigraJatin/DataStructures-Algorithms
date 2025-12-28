// https://leetcode.com/problems/meeting-rooms-iii/
/*
==================== KEY TAKEAWAYS (INTERVIEW REVISION) ====================

1) priority_queue is a *container adaptor*
   - No iterators, no range-for
   - Allowed ops: push(), pop(), top(), empty(), size()
   - pop() returns void → always read top() BEFORE pop()

2) Structured bindings rules
   - Valid ONLY at declaration:
       auto [a, b] = expr;
   - NOT assignable:
       [a, b] = expr;        // ❌ invalid
   - Rebind by re-declaring or using std::tie()

3) pair + greater<> trick
   - priority_queue<pair<T1,T2>, ..., greater<>>
     → min-heap ordered lexicographically
     → first by T1, then T2
   - Perfect for (endTime, roomNo) scheduling

4) Why long long for time
   - Input times fit in int
   - BUT delayed meetings accumulate time
   - Intermediate values can exceed INT_MAX
   - Always use long long for "time" in scheduling problems

5) Correct heap pop pattern
   - ALWAYS:
       auto x = pq.top();
       pq.pop();
   - NEVER:
       auto x = pq.pop();    // ❌ pop() returns void

6) Room availability logic
   - First free all rooms whose meetings ended <= start
   - If no room free:
       - Delay meeting to earliest ending room
       - New end = earliestEnd + duration
   - Guarantees correct greedy behavior

7) Why two heaps
   - roomsInUse: min-heap by (endTime, roomNo)
   - rooms: min-heap of available room numbers
   - Ensures:
       a) earliest finishing room is reused
       b) smallest room index chosen on tie

8) Sorting meetings
   - vector<vector<int>> sorted lexicographically
   - Equivalent to sorting by start time, then end
   - Acceptable but vector<pair<int,int>> is cleaner

9) std::max_element + std::distance
   - Returns FIRST occurrence of max
   - distance(begin, it) gives 0-based index
   - Exactly matches problem requirement

10) Interview mindset
   - Constraints apply to INPUT, not INTERMEDIATE values
   - Safety > cleverness
   - Clean STL + correct types = strong signal

===========================================================================
*/


class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        vector<int> count(n,0);
        // [endTime, RoomNo]
        priority_queue<std::pair<long long,int>, std::vector<std::pair<long long,int>>, std::greater<>> roomsInUse;
        priority_queue<int,vector<int>,greater<int>> rooms;
        
        for(int i = 0 ; i < n ; i++){
            rooms.push(i);
        }
        sort(meetings.begin(), meetings.end());

        // iterate over meetings sorted by start time
        for (const auto& m : meetings) {
            long long start = m[0], end = m[1];
            // finish any meeting that should end at current start time or before it 
            {
                while(!roomsInUse.empty()){
                    auto [endingTime, roomNo] = roomsInUse.top();
                    if(endingTime > start){
                        break;
                    }
                    roomsInUse.pop();
                    // make the room available for use
                    rooms.push(roomNo);
                }
            }

            // if no room is available for current meeting
            if(rooms.empty()){
                // remove the room that will become next available and mark it available
                auto [endingTime, roomNo] = roomsInUse.top();
                roomsInUse.pop();
                rooms.push(roomNo);
                // update current meetings's timings
                end = endingTime + (end - start);
                start = endingTime; // not really needed, added for understanding
            }

            // schedule current meething
            // take the available room
            {
                auto roomNo = rooms.top();
                rooms.pop();
                roomsInUse.push(make_pair(end, roomNo));
                // increase the use of roomNo since current meeting used/will use it
                count[roomNo]++;
            }
	    }


        // find the maximum value in count
        auto it = std::max_element(count.begin(), count.end());
        // find first index at which the value comes
	    int index   = std::distance(count.begin(), it);
        return index;
    }
};