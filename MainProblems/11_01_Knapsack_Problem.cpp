#include <bits/stdc++.h>
using namespace std;

/**
 * 0/1 Knapsack Problem
 *
 * * Given:
 *      - weights[] → weight of each item
 *      - values[]  → value of each item
 *      - W         → capacity of knapsack
 *
 * * We must maximize total value such that:
 *      - Total weight ≤ W
 *      - Each item can be taken at most once (0 or 1)
 *
 * ? Why called 0/1?
 *   Because for each item:
 *      Either take it (1)
 *      Or don't take it (0)
 *
 * Example:
 *   weights = {1, 3, 4, 5}
 *   values  = {1, 4, 5, 7}
 *   W = 7
 *
 *   Best choice:
 *      Take items (3,4) → value = 4 + 5 = 9
 *
 * ===============================================================
 * Approach 1: Brute Force (Recursion)
 * ===============================================================
 *
 * * At every index:
 *      - Take item (if weight allows)
 *      - Skip item
 *
 * * Explore all combinations.
 *
 * Time Complexity:  O(2^n)
 * Space Complexity: O(n) recursion stack
 */

int solveRec(int index, int W, vector<int> &wt, vector<int> &val)
{
    if (index == 0)
    {
        // * If only one item left
        if (wt[0] <= W)
            return val[0];
        else
            return 0;
    }

    // * Option 1: Do not take item
    int notTake = solveRec(index - 1, W, wt, val);

    // * Option 2: Take item (if possible)
    int take = 0;
    if (wt[index] <= W)
        take = val[index] + solveRec(index - 1, W - wt[index], wt, val);

    return max(take, notTake);
}

int BruteforceSolution(vector<int> &wt, vector<int> &val, int W)
{
    int n = wt.size();
    return solveRec(n - 1, W, wt, val);
}

/**
 * ===============================================================
 * Approach 2: Better (Dynamic Programming - Tabulation)
 * ===============================================================
 *
 * * dp[i][w] =
 *      Maximum value using items 0..i
 *      with capacity w
 *
 * Transition:
 *      Not Take → dp[i-1][w]
 *      Take     → val[i] + dp[i-1][w - wt[i]]
 *
 * Time Complexity:  O(n * W)
 * Space Complexity: O(n * W)
 */

int BetterSolution(vector<int> &wt, vector<int> &val, int W)
{
    int n = wt.size();

    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    // * Base case initialization
    for (int w = wt[0]; w <= W; w++)
        dp[0][w] = val[0];

    for (int i = 1; i < n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            int notTake = dp[i - 1][w];

            int take = 0;
            if (wt[i] <= w)
                take = val[i] + dp[i - 1][w - wt[i]];

            dp[i][w] = max(take, notTake);
        }
    }

    return dp[n - 1][W];
}

/**
 * ===============================================================
 * Approach 3: Optimal (Space Optimized DP)
 * ===============================================================
 *
 * * Since dp[i] depends only on dp[i-1],
 *   we can reduce 2D → 1D array.
 *
 * * Traverse weight backwards
 *   to prevent overwriting needed values.
 *
 * Time Complexity:  O(n * W)
 * Space Complexity: O(W)
 */

int OptimalSolution(vector<int> &wt, vector<int> &val, int W)
{
    int n = wt.size();

    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++)
    {
        // * Traverse backwards
        for (int w = W; w >= wt[i]; w--)
        {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }

    return dp[W];
}

int main()
{
    vector<int> weights = {1, 3, 4, 5};
    vector<int> values  = {1, 4, 5, 7};
    int W = 7;

    // int ans = BruteforceSolution(weights, values, W);
    // int ans = BetterSolution(weights, values, W);
    int ans = OptimalSolution(weights, values, W);

    cout << ans;

    return 0;
}
