#include <iostream>
#include <vector>
#include <numeric> // Required for std::iota

using namespace std;

/**
 * DSU (Disjoint Set Union) Implementation
 * * WHY A CLASS INSTEAD OF GLOBAL VECTORS?
 * 1. Encapsulation: All DSU logic is self-contained.
 * 2. Reusability: You can create multiple DSU instances (e.g., dsu1, dsu2).
 * 3. Memory Control: Vectors are initialized only when the object is created.
 */
class DSU {
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        // .resize(n) allocates memory for n integers on the heap.
        // Initially, vectors take ~24 bytes (pointers). 
        // Post-resize: n * sizeof(int) bytes.
        parent.resize(n);
        
        // assign(n, 0) is efficient; it sets size to n and values to 0.
        rank.assign(n, 0); 

        // std::iota is the most idiomatic way to set parent[i] = i
        iota(parent.begin(), parent.end(), 0);
    }

    // Path Compression
    int find(int i) {
        if (parent[i] == i)
            return i;
        // Recursive step + assignment = Path Compression
        return parent[i] = find(parent[i]);
    }

    // Union by Rank
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_i] = root_j;
                rank[root_j]++;
            }
        }
    }

    // Check if two elements are in the same component
    bool isConnected(int i, int j) {
        return find(i) == find(j);
    }

    // Count the total number of disjoint components
    int countComponents() {
        int count = 0;
        for (int i = 0; i < (int)parent.size(); i++) {
            if (parent[i] == i) {  // Only count roots
                count++;
            }
        }
        return count;
    }
};

int main() {
    int n = 5;
    DSU dsu(n);

    cout << "=== INITIAL STATE ===" << endl;
    cout << "Components: " << dsu.countComponents() << " (Expected: 5)" << endl;
    cout << "Is 0 connected to 1? " << (dsu.isConnected(0, 1) ? "Yes" : "No") << " (Expected: No)" << endl;
    cout << endl;

    cout << "=== AFTER UNITE(1, 3) ===" << endl;
    dsu.unite(1, 3);
    cout << "Components: " << dsu.countComponents() << " (Expected: 4)" << endl;
    cout << "Is 1 connected to 3? " << (dsu.isConnected(1, 3) ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "Parent of 3: " << dsu.find(3) << endl;
    cout << endl;

    cout << "=== AFTER UNITE(0, 2) ===" << endl;
    dsu.unite(0, 2);
    cout << "Components: " << dsu.countComponents() << " (Expected: 3)" << endl;
    cout << "Is 0 connected to 2? " << (dsu.isConnected(0, 2) ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << endl;

    cout << "=== TRANSITIVE UNION: UNITE(1, 0) ===" << endl;
    dsu.unite(1, 0);
    cout << "Components: " << dsu.countComponents() << " (Expected: 2)" << endl;
    cout << "Is 3 connected to 2? " << (dsu.isConnected(3, 2) ? "Yes" : "No") << " (Expected: Yes - transitive)" << endl;
    cout << endl;

    cout << "=== EDGE CASE: UNITE(4, 4) ===" << endl;
    dsu.unite(4, 4);  // Uniting element with itself (should be no-op)
    cout << "Components: " << dsu.countComponents() << " (Expected: 2)" << endl;
    cout << endl;

    cout << "=== FINAL STATE ===" << endl;
    cout << "Final number of components: " << dsu.countComponents() << endl;

    return 0;
}

/**
 * ========================================================================
 *                 TYPICAL DSU INTERVIEW PROBLEMS
 * ========================================================================
 *
 * CLASSIC PROBLEMS:
 * • Number of Connected Components in an Undirected Graph (LeetCode 323)
 * • Redundant Connection (LeetCode 684)
 * • Accounts Merge (LeetCode 721)
 * • Number of Islands II (LeetCode 305)
 * • Graph Valid Tree (LeetCode 261)
 * • Friend Circles (LeetCode 547)
 * • Optimize Water Distribution in a Village (LeetCode 1168)
 * • Satisfiability of Equality Equations (LeetCode 990)
 *
 * PATTERN RECOGNITION:
 * 1. Finding connected components → Use countComponents()
 * 2. Checking if two nodes are connected → Use isConnected()
 * 3. Detecting cycles in undirected graphs → If unite() returns false
 * 4. Union of groups with properties → Can track additional metadata
 *
 * EDGE CASES TO HANDLE:
 * • Uniting an element with itself (should be no-op)
 * • Multiple unions creating transitive connections
 * • Querying connectivity before any unions
 * • Disconnected components that never merge
 *
 * ========================================================================
 *                    INTERVIEW REVISION NOTES
 *              Time Complexity & Path Compression
 * ========================================================================
 *
 * 1. WHAT IS PATH COMPRESSION?
 *    In find(i), we don't just return the root; we update parent[i]
 *    to point directly to the root. This "flattens" the tree.
 *
 * 2. WHAT IS UNION BY RANK?
 *    We always attach the shorter tree under the root of the taller
 *    tree. This ensures the tree height only increases when two
 *    trees of equal height are merged.
 *
 * 3. AMORTIZED TIME COMPLEXITY WITH BOTH OPTIMIZATIONS:
 *    When using both Path Compression AND Union by Rank, the time
 *    complexity per operation is O(α(n)), where:
 *
 *    • α (Alpha) is the Inverse Ackermann Function
 *    • For all practical values of n (even atoms in the universe),
 *      α(n) is less than 5
 *    • Therefore, DSU operations are considered "Nearly Constant Time"
 *
 * 4. WHY NOT O(log n)?
 *    Without Path Compression, it would be O(log n). With it, the
 *    structure flattens so aggressively that it becomes faster
 *    than log n.
 *
 * 5. MEMORY RECAP:
 *    • Global vector: ~24 bytes of static memory (BSS segment)
 *    • .resize(n): Triggers one heap allocation of (n * 4) bytes
 *    • .assign(n, 0): Similar to resize, but fills with 0
 *
 * ========================================================================
 */