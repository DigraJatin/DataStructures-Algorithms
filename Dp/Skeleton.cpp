int solve(State)
{
    // 1. Invalid state
    if (invalid)
        return INVALID_VALUE;

    // 2. Base case
    if (base_case)
        return base_answer;

    // 3. Memoization
    if (dp[state] != UNCOMPUTED)
        return dp[state];

    // 4. Compute current state's contribution
    int current = ...;

    // 5. Solve subproblems
    int op1 = solve(...);
    int op2 = solve(...);
    int op3 = solve(...);

    // 6. Combine answers
    int best = max({op1, op2, op3});

    // 7. Handle impossible states
    if (best == INVALID_VALUE)
        return dp[state] = INVALID_VALUE;

    // 8. Store and return
    return dp[state] = current + best;
}