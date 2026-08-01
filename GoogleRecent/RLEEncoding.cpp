class RLE {
    // Time Complexity:
    // Constructor: O(n)
    // get(index): O(log k)
    //
    // Space Complexity:
    // O(k)
    //
    // n = size of original array
    // k = number of runs (groups of consecutive equal characters)
    //
    // Example:
    // Original: A A A B B C C C D
    // Runs:     (A,3) (B,2) (C,3) (D,1)
    // k = 4

    vector<pair<char, int>> runs; // (character, frequency)
    vector<int> prefix;           // prefix[i] = last original index covered by run i

public:
    RLE(vector<char>& chars) {
        int n = chars.size();
        int i = 0;
        int end = -1;

        while (i < n) {
            char curr = chars[i];
            int cnt = 0;

            while (i < n && chars[i] == curr) {
                cnt++;
                i++;
            }

            runs.push_back({curr, cnt});

            end += cnt;
            prefix.push_back(end);
        }
    }

    char get(int index) {
        // First run whose ending index >= index
        int run = lower_bound(prefix.begin(), prefix.end(), index) - prefix.begin();
        return runs[run].first;
    }
};