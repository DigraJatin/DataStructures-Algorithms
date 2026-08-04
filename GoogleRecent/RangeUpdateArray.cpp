// https://enginebogie.com/interview/experience/google-software-development-engineer-3/1794


vector<int> solve(int n, vector<vector<int>>& queries) {
    vector<int> diff(n + 1, 0);

    for (auto& q : queries) {
        int l = q[0];
        int r = q[1];
        int k = q[2];

        diff[l] += k;
        if (r + 1 < n)
            diff[r + 1] -= k;
    }

    vector<int> ans(n);
    ans[0] = diff[0];

    for (int i = 1; i < n; i++)
        ans[i] = ans[i - 1] + diff[i];

    return ans;
}