#include <iostream>
#include <vector>
#include <algorithm> // for ranges::sort
#include <ranges>    // for views and pipes
#include <bit>       // for hardware-accelerated bit ops (C++20)
#include <span>      // for non-owning views of containers
#include <format>    // for cleaner string formatting (C++20/23)

using namespace std;

// 1. MODERN PARAMETER PASSING: std::span (C++20)
// Instead of vector<int>&, use span. It works with vectors, arrays, or raw pointers.
void printFirstTwo(std::span<int> s) {
    if (s.size() >= 2) {
        cout << format("First two: {} and {}\n", s[0], s[1]);
    }
}

int main() {
    // --- PART 1: BIT MANIPULATION (The <bit> Header) ---
    unsigned int n = 5; // Binary: 101
    
    // Old way: while(n) { n >>= 1; count++; }
    // Modern way: bit_width tells you exactly how many bits a number occupies.
    int width = std::bit_width(n); // Result: 3
    
    // Check if power of 2 (Replaces n & (n-1) == 0)
    bool isPow2 = std::has_single_bit(16u); 
    
    // Count set bits (Replaces __builtin_popcount)
    int setBits = std::popcount(7u); // Result: 3

    cout << format("n=5 has width {}, is 16 a power of 2? {}\n", width, isPow2);


    // --- PART 2: RANGES & VIEWS (The Pipe Operator) ---
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // "Views" are lazy: they don't create a new vector, they just define a 'plan'.
    // Here we filter even numbers, square them, and reverse the order.
    auto result = nums 
        | views::filter([](int x) { return x % 2 == 0; }) 
        | views::transform([](int x) { return x * x; })
        | views::reverse;

    cout << "Processed Evens (Reversed): ";
    for (int v : result) cout << v << " "; // 100 64 36 16 4
    cout << "\n";


    // --- PART 3: ENUMERATE (C++23) ---
    // Finally, we can get index and value simultaneously like Python!
    cout << "Indices and Values:\n";
    for (auto [idx, val] : views::enumerate(nums | views::take(3))) {
        cout << format("Index {}: Value {}\n", idx, val);
    }


    // --- PART 4: RANGES ALGORITHMS ---
    // No more v.begin(), v.end()!
    vector<int> unsorted = {5, 1, 9, 3};
    std::ranges::sort(unsorted); // Sorts the whole container directly


    // --- PART 5: CONVERTING VIEWS (C++23 std::ranges::to) ---
    // Sometimes you want to turn a filtered "view" back into a real vector.
    auto evenVec = nums 
                 | views::filter([](int x) { return x % 2 == 0; }) 
                 | std::ranges::to<vector<int>>(); 

    
    // --- PART 6: SPAN DEMO ---
    int arr[] = {10, 20, 30};
    printFirstTwo(nums); // Works with vector
    printFirstTwo(arr);  // Works with C-style array!


    return 0;
}