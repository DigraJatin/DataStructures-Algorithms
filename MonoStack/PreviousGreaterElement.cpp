#include <vector>
#include <iostream>
#include <stack>

using namespace std;

/*
Compute Previous Greater Element to the Left
Traverse Left -> Right
Maintain decreasing stack, top is the answer
*/
vector<int> prevGreaterLeft_LtoR(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // stores indices

    for (int i = 0; i < n; i++) {
        while (!st.empty() && nums[st.top()] <= nums[i]) {
            st.pop();
        }

        if (!st.empty()) {
            result[i] = nums[st.top()];
        }
        st.push(i);
    }

    return result;
}

/*
Compute Previous Greater Element to the Left
Traverse Right -> Left
Resolve answers when stack elements get a greater value
*/
vector<int> prevGreaterLeft_RtoL(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // stores indices

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }

    return result;
}

void printVector(const vector<int>& v) {
    for (int x : v)
        cout << x << " ";
    cout << endl;
}

int main() {

    vector<vector<int>> tests = {
        {3,2,5,10,2,3},
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

        auto r1 = prevGreaterLeft_LtoR(arr);
        auto r2 = prevGreaterLeft_RtoL(arr);

        printVector(arr);
        printVector(r1);
        printVector(r2);

        cout << (r1 == r2) << endl;
        cout << "------\n";
    }

    return 0;
}
