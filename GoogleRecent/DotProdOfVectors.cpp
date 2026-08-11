class SparseVector {
    vector<pair<int, int>> v;

public:
    SparseVector(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0)
                v.push_back({i, nums[i]});
        }
    }

    int dotProduct(SparseVector& vec) {
        int i = 0, j = 0;
        int ans = 0;

        while (i < v.size() && j < vec.v.size()) {
            if (v[i].first == vec.v[j].first) {
                ans += v[i].second * vec.v[j].second;
                i++;
                j++;
            }
            else if (v[i].first < vec.v[j].first) {
                i++;
            }
            else {
                j++;
            }
        }

        return ans;
    }
};