#include <bits/stdc++.h>
using namespace std;

/**
 * House Robber Problem
 *
 * * Given an array nums where:
 *      nums[i] = money in ith house
 *
 * * You cannot rob two adjacent houses.
 *
 * * Return the maximum amount of money you can rob.
 *
 * Example:
 *   nums = {2, 7, 9, 3, 1}
 *
 *   Best choice:
 *      Rob 2 + 9 + 1 = 12
 *
 *   Answer = 12
 *
 * ===============================================================
 * Approach 1: Brute Force (Recursion)
 * ===============================================================
 *
 * * At each index:
 *      - Rob current house → move to index-2
 *      - Skip current house → move to index-1
 *
 * Time Complexity:  O(2^n)
 * Space Complexity: O(n)
 */

int solveRec(int index, vector<int> &nums)
{
    if (index < 0)
        return 0;

    if (index == 0)
        return nums[0];

    // * Option 1: Rob current house
    int take = nums[index] + solveRec(index - 2, nums);

    // * Option 2: Skip current house
    int notTake = solveRec(index - 1, nums);

    return max(take, notTake);
}

int BruteforceSolution(vector<int> &nums)
{
    return solveRec(nums.size() - 1, nums);
}

/**
 * ===============================================================
 * Approach 2: Better (DP - Tabulation)
 * ===============================================================
 *
 * * dp[i] =
 *      Maximum money we can rob from first i houses.
 *
 * Transition:
 *   dp[i] = max(
 *      nums[i] + dp[i-2],  // rob
 *      dp[i-1]             // skip
 *   )
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(n)
 */

int BetterSolution(vector<int> &nums)
{
    int n = nums.size();
    if (n == 1)
        return nums[0];

    vector<int> dp(n);

    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for (int i = 2; i < n; i++)
    {
        dp[i] = max(
            nums[i] + dp[i - 2],
            dp[i - 1]
        );
    }

    return dp[n - 1];
}

/**
 * ===============================================================
 * Approach 3: Optimal (Space Optimized DP)
 * ===============================================================
 *
 * * Since dp[i] depends only on dp[i-1] and dp[i-2],
 *   we can store only two variables.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */

int OptimalSolution(vector<int> &nums)
{
    int n = nums.size();
    if (n == 1)
        return nums[0];

    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);

    for (int i = 2; i < n; i++)
    {
        int curr = max(
            nums[i] + prev2,
            prev1
        );

        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main()
{
    vector<int> nums = {2, 7, 9, 3, 1};

    // int ans = BruteforceSolution(nums);
    // int ans = BetterSolution(nums);
    int ans = OptimalSolution(nums);

    cout << ans;

    return 0;
}
