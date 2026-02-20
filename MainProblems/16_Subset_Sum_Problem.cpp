#include <bits/stdc++.h>
using namespace std;

/**
 * Subset Sum Problem
 *
 * * Given:
 *      - nums[] → array of positive integers
 *      - target → required sum
 *
 * * Determine whether there exists a subset
 *   whose sum is exactly equal to target.
 *
 * ! Each element can be used at most once.
 *
 * ===============================================================
 * Example 1:
 *   nums = {3, 34, 4, 12, 5, 2}
 *   target = 9
 *
 *   Subset:
 *      4 + 5 = 9
 *
 *   Answer = true
 *
 * ---------------------------------------------------------------
 *
 * Example 2:
 *   nums = {1, 2, 3}
 *   target = 7
 *
 *   No subset forms 7
 *
 *   Answer = false
 *
 * ---------------------------------------------------------------
 *
 * Example 3:
 *   nums = {2, 3, 7, 8, 10}
 *   target = 11
 *
 *   Subset:
 *      3 + 8 = 11
 *
 *   Answer = true
 *
 * ===============================================================
 * Approach 1: Brute Force (Recursion)
 * ===============================================================
 *
 * * At each index:
 *      - Take the element
 *      - Skip the element
 *
 * Time Complexity:  O(2^n)
 * Space Complexity: O(n)
 */

bool solveRec(int index, int target, vector<int> &nums)
{
    if (target == 0)
        return true;

    if (index == 0)
        return nums[0] == target;

    bool notTake = solveRec(index - 1, target, nums);

    bool take = false;
    if (nums[index] <= target)
        take = solveRec(index - 1, target - nums[index], nums);

    return take || notTake;
}

bool BruteforceSolution(vector<int> &nums, int target)
{
    int n = nums.size();
    return solveRec(n - 1, target, nums);
}

/**
 * ===============================================================
 * Approach 2: Better (DP - Tabulation)
 * ===============================================================
 *
 * * dp[i][t] =
 *      true if subset from 0..i forms sum t
 *
 * Transition:
 *      Not Take → dp[i-1][t]
 *      Take     → dp[i-1][t - nums[i]]
 *
 * Time Complexity:  O(n * target)
 * Space Complexity: O(n * target)
 */

bool BetterSolution(vector<int> &nums, int target)
{
    int n = nums.size();

    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    for (int i = 0; i < n; i++)
        dp[i][0] = true;  // sum 0 always possible

    if (nums[0] <= target)
        dp[0][nums[0]] = true;

    for (int i = 1; i < n; i++)
    {
        for (int t = 1; t <= target; t++)
        {
            bool notTake = dp[i - 1][t];

            bool take = false;
            if (nums[i] <= t)
                take = dp[i - 1][t - nums[i]];

            dp[i][t] = take || notTake;
        }
    }

    return dp[n - 1][target];
}

/**
 * ===============================================================
 * Approach 3: Optimal (Space Optimized DP)
 * ===============================================================
 *
 * * Since dp[i] depends only on previous row,
 *   we can use 1D array.
 *
 * ! Traverse backwards to avoid overwriting needed values.
 *
 * Time Complexity:  O(n * target)
 * Space Complexity: O(target)
 */

bool OptimalSolution(vector<int> &nums, int target)
{
    int n = nums.size();

    vector<bool> dp(target + 1, false);

    dp[0] = true;

    if (nums[0] <= target)
        dp[nums[0]] = true;

    for (int i = 1; i < n; i++)
    {
        for (int t = target; t >= nums[i]; t--)
        {
            dp[t] = dp[t] || dp[t - nums[i]];
        }
    }

    return dp[target];
}

int main()
{
    vector<int> nums = {3, 34, 4, 12, 5, 2};
    int target = 9;

    // bool ans = BruteforceSolution(nums, target);
    // bool ans = BetterSolution(nums, target);
    bool ans = OptimalSolution(nums, target);

    cout << (ans ? "True" : "False");

    return 0;
}
