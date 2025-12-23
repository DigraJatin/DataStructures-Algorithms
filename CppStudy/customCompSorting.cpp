#include <bits/stdc++.h>
using namespace std;

auto defaultComparator = [](const vector<int>& a, const vector<int>& b) {
    // returns true if a should come before b
    if(a[0] != b[0]) return a[0] < b[0];
    if(a[1] != b[1]) return a[1] < b[1];
    return a[2] < b[2];
    // this is exactly same as default lexicographical order
};

auto customComparator = [](const vector<int>& a, const vector<int>& b) {
    // custom sorting: first by 2nd index, then by 3rd index, then by 1st index
    if(a[1] != b[1]) return a[1] < b[1];
    if(a[2] != b[2]) return a[2] < b[2];
    return a[0] < b[0];
};

void print2DVector(const vector<vector<int>>& vec) {
    for (const auto& row : vec) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int main(){
    vector<vector<int>> arr = {
        {2, 5, 1},
        {1, 9, 3},
        {2, 3, 7},
        {1, 4, 6},
        {1, 4, 2}
    };


    // print inital array
    cout << "Initial array:" << endl;
    print2DVector(arr);

    // do default sort that uses lexicographical order i.e, 0->1->2 index wise
    sort(arr.begin(), arr.end());
    cout << "\nArray after default sort (lexicographical order):" << endl;
    print2DVector(arr);

    arr = {
        {2, 5, 1},
        {1, 9, 3},
        {2, 3, 7},
        {1, 4, 6},
        {1, 4, 2}
    };

    // default sort can also be done using a comparator function that matches the default behavior
    sort(arr.begin(), arr.end(), defaultComparator);
    cout << "\nArray after sorting with defaultComparator:" << endl;
    print2DVector(arr);

    // custom sorting: first by 2nd index, then by 3rd index, then by 1st index
    sort(arr.begin(), arr.end(), customComparator);
    cout << "\nArray after custom sort (by 2nd, then 3rd, then 1st index):" << endl;
    print2DVector(arr);  

    return 0;
}