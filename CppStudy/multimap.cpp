// Multimap is a container that stores key-value pairs in sorted order by key
// Unlike std::map, multimap ALLOWS DUPLICATE KEYS
// It's implemented as a balanced binary search tree (Red-Black Tree)
// Time complexity: O(log n) for insert, find, delete
// Order: SORTED by key (automatically maintained)

#include <bits/stdc++.h>

int main(){

    // Declare a multimap: key=student name, value=grade
    // Template: multimap<KeyType, ValueType>
    std::multimap<std::string, char> grades;

    // Insert key-value pairs using insert()
    // Elements are automatically sorted by key
    grades.insert({"Alice", 'A'});
    grades.insert({"Bob", 'B'});
    grades.insert({"Charlie", 'C'});
    grades.insert({"Alice", 'A+'}); // Duplicate keys allowed - Alice has two grades

    // Alternative: use emplace() for in-place construction
    // Functionally similar to insert() but can be slightly more efficient
    grades.emplace("David", 'B');
    grades.emplace("David", 'A');

    // Check if a key exists using find()
    // Note: multimap does NOT support [] operator (only map does)
    // .find() returns an iterator to the FIRST occurrence of the key
    // Returns .end() if key not found
    
    if(grades.find("Alice") != grades.end()){
        std::cout << "Alice found in grades multimap\n";
    } else {
        std::cout << "Alice not found in grades multimap\n";
    }

    // Iterate through ALL elements in sorted order
    // Structured binding [name, grade] unpacks the pair<key, value>
    // Order is: Alice, Alice, Bob, Charlie, David, David (sorted by key)
    std::cout << "All grades:\n";
    for(const auto& [name, grade] : grades){
        std::cout << name << ": " << grade << "\n";
    }

    // Find ALL occurrences of a specific key using equal_range()
    // Returns a pair of iterators: [first, second)
    //   - range.first  = iterator to FIRST occurrence of "David"
    //   - range.second = iterator to FIRST element AFTER all "David" entries
    // All David entries are contiguous due to sorted order maintained by multimap
    // This is more efficient than calling find() multiple times
    
    std::cout << "Grades of David:\n";
    auto range = grades.equal_range("David"); // log(n)
    for(auto it = range.first; it != range.second; ++it){
        std::cout << it->first << ": " << it->second << "\n";
    }

    // INEFFICIENT - Multiple binary searches
    // auto it = grades.find("David");  // 1st search: O(log n)
    // if(it != grades.end()) {
    //     std::cout << it->first << ": " << it->second << "\n";
    //     ++it;  // Move to next element
    // }
    // But how do you know when David entries end? 
    // You'd need MORE find() calls or manual checking

    // that's it!

    return 0;
}