#include <vector>
#include <iostream>
#include <stack>

using namespace std;

/*
Single pass to compute both:
  - Next Greater Element to the Right (NGE) — strictly greater
  - Previous Greater Element to the Left (PGE) — NOT strict (equals count as greater)

Pop condition: < (strict)
  - NGE is strict: we only pop when nums[i] is truly greater than st.top()
  - PGE is NOT strict: equal elements stay on the stack, so st.top() after
    pop may be an equal value (e.g. {4,4} -> PGE = [-1, 4])

If strict PGE is also needed, use <= instead — but then NGE becomes non-strict.
You can't get both strict in a single pass; use separate passes.
*/
pair<vector<int>, vector<int>> ngeAndPge_SinglePass(const vector<int>& nums) {
    int n = nums.size();
    vector<int> nge(n, -1);  // next strictly greater to the right
    vector<int> pge(n, -1);  // previous greater-or-equal to the left
    stack<int> st;

    for (int i = 0; i <= n; i++) {
        // i == n: sentinel (-infinity) to flush all remaining elements
        while (!st.empty() && (i == n || nums[st.top()] < nums[i])) {
            int mid = st.top(); st.pop();
            // nums[i] > nums[mid], so nums[i] is the next strictly greater
            nge[mid] = (i < n) ? nums[i] : -1;
            // st.top() after pop is the nearest left element that was >= nums[mid]
            // (equals stay on stack since we use <, so this may be an equal, not strictly greater)
            pge[mid] = st.empty() ? -1 : nums[st.top()];
        }
        st.push(i);
    }

    return {nge, pge};
}

void printVector(const vector<int>& v) {
    for (int x : v)
        cout << x << " ";
    cout << endl;
}

int main() {

    vector<vector<int>> tests = {
        {1,5,7,2,6,3,1},
        {5,4,3,2,1},          // strictly decreasing
        {1,2,3,4,5},          // strictly increasing
        {4,8,5,2,25},
        {3,3,3},              // all equal
        {2,1,2,4,3},
        {7},                  // single element
        {1,1},                // two equal
        {2,1},                // two decreasing
        {1,2},                // two increasing
        {10,5,10,5,10},       // alternating high-low
        {3,1,4,1,5,9,2,6},   // mixed with duplicates
        {5,5,5,4,4,4,3,3,3}, // plateaus descending
        {1,3,2,4,3,5,4},     // zigzag
        {100,1,100,1,100},   // large gap alternating
    };

    for (auto& arr : tests) {
        auto [nge, pge] = ngeAndPge_SinglePass(arr);

        cout << "arr: "; printVector(arr);
        cout << "nge: "; printVector(nge);
        cout << "pge: "; printVector(pge);
        cout << "------\n";
    }

    return 0;
}
