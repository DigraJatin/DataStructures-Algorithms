// In a std::priority_queue, the primary difference between .push() and .emplace() lies in how the object is constructed and moved into the container.
// .push(): Takes an already existing object (or a temporary) and inserts a copy or a move of it into the queue.
// .emplace(): Constructs the object in-place directly inside the underlying container by forwarding arguments to the element's constructor. 

#include <iostream>
#include <queue>
#include <string>  

struct Task {
    int priority{} ;
    std::string details{};

    // CTor
    Task(int p, std::string d) : priority(p), details(d) {
        std::cout<< "Task Created: "<< details << std::endl;
    }

    // required for max heap
    bool operator < (const Task& other) const {
        return priority < other.priority;
    }

    // required for min heap
    bool operator > (const Task& other) const {
        return priority > other.priority;
    }
};

int main(){
    std::priority_queue<Task, std::vector<Task>, std::greater<Task>> pq;


    // Using .push, requires to create a temporary task first
    Task A(1, "Jatin's DB Project");
    pq.push(A);
    pq.push(Task(2, "Find a Date for Valentines"));
    // a temporary object is create in both above examples and then moved/copied

    // Using .emplace
    // arguments are passed directly, no temporary object created
    pq.emplace(3, "Prepare for C++ Exam");

    std::cout << "Top Priority Task: " << pq.top().details << " with priority " << pq.top().priority << std::endl;  
    return 0;
}