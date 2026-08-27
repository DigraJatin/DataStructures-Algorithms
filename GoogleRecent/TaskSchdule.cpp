// This round was based on task scheduling.
// First part: Given multiple tasks (all with equal execution time) and a set of machines, determine the earliest time by which all tasks can be completed.
// Second part: Given the number of tasks and execution time, find the minimum number of CPUs required to achieve that earliest completion time.
// The key idea here involved combining scheduling logic with binary search to optimize resource usage.

// given m cpu's find earliert completion time
// each task takes same time t and N independent tasks with m cpu's
// each cpu can execute 1 task every t time units
// every batch of t seconds m tasks can be finished
// no of batches = n/m
// total time = n/m * t

// Minimum cpu's needed to achieve given earlies time ?
// Target time T
// each CPU execute T/t tasks
// m cpu capacity = m*T/t
// we need m*T/t >= N
// m = N/(T/t)


// lc problem
// https://neetcode.io/solutions/task-scheduler


// google variant

// A CPU task is Task(id, queued_time, exec_time). 
// Given a collection of tasks, 
// return the execution order of task ids processed by a single-core CPU. 
// When the CPU is idle and multiple tasks are queued, 
// it picks the one with the smallest exec_time first. 
// Example: (1,2,2),(2,5,15),(3,5,10) -> output 1,3,2. 

// Follow-up: what if each task also had a priority?

// The CPU follows:

// Tasks become available when queued_time <= current_time.
// If there are multiple available tasks, choose:
// smallest exec_time
// if tied, usually smallest id (important tie-breaker to establish deterministic order).
// Execute it completely.
// Repeat.
// If no task is available, jump current_time to the next task's queued_time.

// So this is:

// Sort by arrival time + min-heap by execution time.

class Solution {
    struct Task {
        int id;
        int queued_time;
        int exec_time;
    };

    struct sortComp {
        bool operator()(const Task& a, const Task& b) {
            return a.queued_time < b.queued_time;
        }
    };

    struct pqComp {
        bool operator()(const Task& a, const Task& b) {
            if (a.exec_time != b.exec_time) {
                return a.exec_time > b.exec_time;
            }
            return a.id > b.id;
        }
    };

public:
    vector<int> getOrder(vector<Task>& tasks) {
        sort(tasks.begin(), tasks.end(), sortComp());

        priority_queue<Task, vector<Task>, pqComp> pq;

        vector<int> ans;
        long long time = 0;
        int i = 0, n = tasks.size();

        while (i < n || !pq.empty()) {

            if (pq.empty() && time < tasks[i].queued_time) {
                time = tasks[i].queued_time;  // fixed
            }

            while (i < n && tasks[i].queued_time <= time) {
                pq.push(tasks[i++]);
            }

            Task curr = pq.top();
            pq.pop();

            ans.push_back(curr.id);           // fixed
            time += curr.exec_time;
        }

        return ans;
    }
};

// O(NLogN) + O(N)