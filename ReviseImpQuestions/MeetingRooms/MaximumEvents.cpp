// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());
        int n = events.size();
        int lastDay = std::max_element(events.begin(), events.end(),
            [](const auto& a, const auto& b) {
                return a[1] < b[1];
            }
        )->at(1);
        int retVal = 0;
        // stores end day of events
        std::priority_queue<int, vector<int>, std::greater<>> pq;

        for(int i = 0, j=0 ; i <= lastDay ; i++){
            // add all events in pq that have start day <= curr day
            while(j < n && events[j][0] <= i){
                pq.push(events[j][1]);
                j++;
            }

            // check if any events in pq should end i.e, end day < today
            while(!pq.empty() && pq.top() < i){
                pq.pop();
            }

            // left event must have end day >= curr day, attend that event today
            if(!pq.empty()){
                pq.pop();
                retVal++;
            }
        }
        
        return retVal;
    }
};