class Solution {
public:
    vector<int> bricks;
    int targetWidth;
    const int MOD = 1e9 + 7;
    vector<vector<int>> validRows;  // All valid brick arrangements for a single row
    vector<int> currentRow;         // Temporary vector for building row combinations

    int buildWall(int height, int width, vector<int>& bricks) {
        this->targetWidth = width;
        this->bricks = bricks;

        // Step 1: Generate all valid brick arrangements for a single row
        generateValidRows(0);

        // Clear temporary vector after use
        currentRow.clear();

        int numRows = validRows.size();

        // Step 2: Build adjacency graph - which rows can be placed on top of each other
        vector<vector<int>> adjacencyGraph(numRows);
        for (int i = 0; i < numRows; ++i) {
            // Check if row i can be placed on top of itself
            if (canStack(validRows[i], validRows[i])) {
                adjacencyGraph[i].push_back(i);
            }
            // Check if row i can be placed on top of row j (and vice versa)
            for (int j = i + 1; j < numRows; ++j) {
                if (canStack(validRows[i], validRows[j])) {
                    adjacencyGraph[i].push_back(j);
                    adjacencyGraph[j].push_back(i);
                }
            }
        }

        // Step 3: Dynamic programming to count valid wall configurations
        // dp[i][j] = number of ways to build wall of height i+1 with row j on top
        vector<vector<int>> dp(height, vector<int>(numRows));

        // Base case: first row can be any valid row arrangement
        for (int j = 0; j < numRows; ++j) {
            dp[0][j] = 1;
        }

        // Fill dp table for remaining heights
        for (int i = 1; i < height; ++i) {
            for (int j = 0; j < numRows; ++j) {
                // Sum up ways from all compatible previous rows
                for (int prevRow : adjacencyGraph[j]) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][prevRow]) % MOD;
                }
            }
        }

        // Step 4: Calculate total number of valid walls
        int totalWays = 0;
        for (int j = 0; j < numRows; ++j) {
            totalWays = (totalWays + dp[height - 1][j]) % MOD;
        }

        return totalWays;
    }

private:
    // Check if two rows can be stacked (no vertical joints align)
    bool canStack(vector<int>& rowA, vector<int>& rowB) {
        int sumA = rowA[0];  // Running sum of bricks in row A
        int sumB = rowB[0];  // Running sum of bricks in row B
        int indexA = 1;
        int indexB = 1;

        // Compare cumulative widths to find if any joints align
        while (indexA < rowA.size() && indexB < rowB.size()) {
            if (sumA == sumB) {
                // Found aligned joint (except at the end)
                return false;
            }
            // Advance the row with smaller cumulative width
            if (sumA < sumB) {
                sumA += rowA[indexA++];
            } else {
                sumB += rowB[indexB++];
            }
        }
        return true;  // No aligned joints found
    }

    // Generate all valid brick arrangements for a single row using DFS
    void generateValidRows(int currentWidth) {
        // Prune if we exceed target width
        if (currentWidth > targetWidth) {
            return;
        }

        // Found a valid row arrangement
        if (currentWidth == targetWidth) {
            validRows.push_back(currentRow);
            return;
        }

        // Try adding each brick type
        for (int brickSize : bricks) {
            currentRow.push_back(brickSize);
            generateValidRows(currentWidth + brickSize);
            currentRow.pop_back();  // Backtrack
        }
    }
};
