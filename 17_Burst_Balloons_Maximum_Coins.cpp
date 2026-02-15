#include <bits/stdc++.h>
using namespace std;

/**
 * Burst Balloons (Maximum Coins)
 *
 * * You are given an array nums.
 * * When you burst balloon i, you gain:
 *
 *      nums[left] * nums[i] * nums[right]
 *
 *   where left and right are the NEAREST balloons
 *   still present after previous bursts.
 *
 * ! Important:
 *   It does NOT mean i-1 and i+1 from original array.
 *   Neighbors change dynamically as balloons disappear.
 *
 * ---------------------------------------------------------------
 * Explanation Example:
 *
 *   nums = {1, 2, 3, 4}
 *
 *   If we burst 2 first:
 *      Neighbors = 1 and 3
 *      Coins = 1 * 2 * 3 = 6
 *
 *   Array becomes:
 *      {1, 3, 4}
 *
 *   If we then burst 3:
 *      Neighbors = 1 and 4
 *      Coins = 1 * 3 * 4 = 12
 *
 *   Array becomes:
 *      {1, 4}
 *
 *   So only the burst balloon disappears.
 *   The array shrinks gradually.
 *
 * ---------------------------------------------------------------
 *
 * Key Insight (Very Important):
 *
 * Instead of thinking:
 *   "Which balloon should I burst first?"
 *
 * Think:
 *   "Which balloon should I burst LAST in a range?"
 *
 * Why?
 * Because when bursting last in a subarray [i, j],
 * its neighbors will definitely be:
 *
 *      nums[i-1] and nums[j+1]
 *
 * This removes dynamic neighbor complexity.
 *
 * ---------------------------------------------------------------
 *
 * We add artificial boundaries:
 *      1 at beginning
 *      1 at end
 *
 * So:
 *      nums = {3,1,5,8}
 * becomes:
 *      {1,3,1,5,8,1}
 *
 * ---------------------------------------------------------------
 *
 * Example 1:
 *   nums = {3, 1, 5, 8}
 *
 *   Maximum coins = 167
 *
 * ---------------------------------------------------------------
 *
 * Example 2:
 *   nums = {1, 5}
 *
 *   Maximum coins = 10
 *
 * ---------------------------------------------------------------
 *
 * Example 3:
 *   nums = {7}
 *
 *   Maximum coins = 7
 *
 * ===============================================================
 * Approach 1: Brute Force (Recursion)
 * ===============================================================
 *
 * * Try each balloon as LAST burst in range [i, j].
 *
 * Time Complexity: Exponential
 * Space Complexity: O(n)
 */

int solveRec(int i, int j, vector<int> &nums)
{
    if (i > j)
        return 0;

    int maxi = 0;

    for (int k = i; k <= j; k++)
    {
        int coins =
            nums[i - 1] * nums[k] * nums[j + 1] +
            solveRec(i, k - 1, nums) +
            solveRec(k + 1, j, nums);

        maxi = max(maxi, coins);
    }

    return maxi;
}

int BruteforceSolution(vector<int> nums)
{
    int n = nums.size();

    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    return solveRec(1, n, nums);
}

/**
 * ===============================================================
 * Approach 2: Better (Memoization)
 * ===============================================================
 *
 * * Store dp[i][j] =
 *      Maximum coins from bursting balloons in range [i, j]
 *
 * Time Complexity:  O(n^3)
 * Space Complexity: O(n^2)
 */

int solveMemo(int i, int j, vector<int> &nums, vector<vector<int>> &dp)
{
    if (i > j)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int maxi = 0;

    for (int k = i; k <= j; k++)
    {
        int coins =
            nums[i - 1] * nums[k] * nums[j + 1] +
            solveMemo(i, k - 1, nums, dp) +
            solveMemo(k + 1, j, nums, dp);

        maxi = max(maxi, coins);
    }

    return dp[i][j] = maxi;
}

int BetterSolution(vector<int> nums)
{
    int n = nums.size();

    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));

    return solveMemo(1, n, nums, dp);
}

/**
 * ===============================================================
 * Approach 3: Optimal (Bottom-Up DP)
 * ===============================================================
 *
 * * Fill dp table from smaller ranges to larger ranges.
 *
 * Time Complexity:  O(n^3)
 * Space Complexity: O(n^2)
 */

int OptimalSolution(vector<int> nums)
{
    int n = nums.size();

    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    for (int len = 1; len <= n; len++)
    {
        for (int i = 1; i <= n - len + 1; i++)
        {
            int j = i + len - 1;

            for (int k = i; k <= j; k++)
            {
                dp[i][j] = max(
                    dp[i][j],
                    nums[i - 1] * nums[k] * nums[j + 1] +
                    dp[i][k - 1] +
                    dp[k + 1][j]
                );
            }
        }
    }

    return dp[1][n];
}

int main()
{
    vector<int> nums = {3, 1, 5, 8};

    // int ans = BruteforceSolution(nums);
    // int ans = BetterSolution(nums);
    int ans = OptimalSolution(nums);

    cout << ans;

    return 0;
}
