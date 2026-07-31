// ============================================================================
// Problem:
// Given a weighted graph and a node X, remove X along with all its incident
// edges and return the maximum edge weight remaining in the graph.

// Example:
// Edges:
// (A,B,5), (A,C,2), (A,D,8), (C,D,6), (D,E,7), (B,E,4)

// Remove A:
// Remaining edges -> (C,D,6), (D,E,7), (B,E,4)
// Answer = 7

// Follow-up:
// Multiple queries on the same graph.

// ----------------------------------------------------------------------------
// Approach 1 : Brute Force
// For every query, scan all edges and ignore edges incident to the removed node.

// Time : O(E) per query
// Space: O(1)

// ----------------------------------------------------------------------------
// Approach 2 : Max Heap
// Store all edges in a max heap ordered by weight.
// For a query, keep popping until the top edge is not incident to the removed
// node.

// Build : O(E log E)
// Query : O(E log E) worst case
// Space : O(E)

// ----------------------------------------------------------------------------
// Approach 3 : Multiset
// Maintain all edge weights inside a multiset and keep adjacency information
// for every node.

// On removing a node, erase all incident edge weights from the multiset.
// Maximum remaining edge = *multiset.rbegin().

// Suitable when deletions are PERMANENT.

// Build : O(E log E)
// Query : O(degree(node) * log E)
// Space : O(E)

// ----------------------------------------------------------------------------
// Approach 4 : Preprocessing (Static Graph, Multiple Queries)
// Precompute answer[node] = maximum edge remaining after removing 'node'.

// Simple preprocessing:
// For every node, scan every edge and ignore incident edges.

// Preprocessing : O(V * E)
// Query         : O(1)
// Space         : O(V)

// ----------------------------------------------------------------------------
// Discussion / Possible Optimization
// Observation:
// The globally maximum edge is invalid only for its two endpoints.
// Removing any other node does not affect it.

// There may exist a more optimal preprocessing using an auxiliary data
// structure (often discussed in interviews), but for a general graph the
// exact optimal algorithm depends on additional constraints or hints.

// The Missing Data Structure

// This is the interesting interview part.

// You now ask

// "How do I efficiently assign this weight to every node except two?"

// Possible answers include:

// Segment Tree with lazy propagation (if nodes are indexed and updates have structure).
// Bitsets to batch assignments.
// Union-Find "next unassigned" trick (offline processing).
// Balanced BST of unanswered nodes.

// The interviewer is often testing whether you recognize the pattern of offline processing rather than expecting a specific graph algorithm.

// ============================================================================