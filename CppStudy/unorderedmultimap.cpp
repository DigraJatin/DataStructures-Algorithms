// Unordered_multimap is a container that stores key-value pairs WITHOUT any order
// Like multimap, unordered_multimap ALLOWS DUPLICATE KEYS
// It's implemented as a HASH TABLE (not a tree)
// Time complexity: O(1) average for insert, find, delete (vs O(log n) for multimap)
// Order: NO ORDER GUARANTEED - depends on hash function
// IMPORTANT: unordered_multimap also does NOT support [] operator (like multimap)

#include <bits/stdc++.h>

int main(){

    // Declare an unordered_multimap: key=student name, value=grade
    // Template: unordered_multimap<KeyType, ValueType>
    // Requires a hash function for the key type (std::string has a built-in hash)
    std::unordered_multimap<std::string, char> grades;

    // Insert key-value pairs using insert()
    // Elements are stored based on hash value, NOT in sorted order
    grades.insert({"Alice", 'A'});
    grades.insert({"Bob", 'B'});
    grades.insert({"Charlie", 'C'});
    grades.insert({"Alice", 'A'}); // Duplicate keys allowed - Alice has two grades

    // Alternative: use emplace() for in-place construction
    // Functionally similar to insert() but can be slightly more efficient
    grades.emplace("David", 'B');
    grades.emplace("David", 'A');

    // Check if a key exists using find()
    // Note: unordered_multimap ALSO does NOT support [] operator (like multimap)
    // Both map types prevent [] access for safety and performance reasons
    // .find() returns an iterator to ONE occurrence of the key
    // Returns .end() if key not found
    
    if(grades.find("Alice") != grades.end()){
        std::cout << "Alice found in grades unordered_multimap\n";
    } else {
        std::cout << "Alice not found in grades unordered_multimap\n";
    }

    // Iterate through ALL elements - NO GUARANTEED ORDER
    // Output order is unpredictable - depends on hash function
    // You might see: David, Alice, Bob, Charlie, Alice, David (or any other order)
    // Structured binding [name, grade] still unpacks the pair<key, value>
    std::cout << "\nAll grades (NO ORDER GUARANTEED):\n";
    for(const auto& [name, grade] : grades){
        std::cout << name << ": " << grade << "\n";
    }

    // Find ALL occurrences of a specific key using equal_range()
    // Returns a pair of iterators: [first, second)
    //   - range.first  = iterator to AN occurrence of "David" (not necessarily first!)
    //   - range.second = iterator to FIRST element AFTER all "David" entries
    // All David entries are still contiguous due to hash table bucket structure
    // But they WON'T be in any particular order
    // This is still O(k) where k = number of "David" entries (faster than O(log n + k))
    
    std::cout << "\nGrades of David (using equal_range):\n";
    auto range = grades.equal_range("David");
    for(auto it = range.first; it != range.second; ++it){
        std::cout << it->first << ": " << it->second << "\n";
    }

    // Additional: Get bucket statistics (unique to hash tables)
    std::cout << "\nHash table stats:\n";
    std::cout << "Total buckets: " << grades.bucket_count() << "\n";
    std::cout << "Total elements: " << grades.size() << "\n";
    std::cout << "Load factor: " << grades.load_factor() << "\n";

    // that's it!

    return 0;
}
