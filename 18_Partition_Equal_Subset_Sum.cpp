#include <bits/stdc++.h>
using namespace std;

/**
 * Partition Equal Subset Sum
 *
 * * Given an integer array nums,
 *   return true if the array can be partitioned
 *   into two subsets such that:
 *
 *        sum(subset1) == sum(subset2)
 *
 * ---------------------------------------------------------------
 * Key Idea:
 *
 * * Let totalSum = sum of all elements.
 *
 * * If totalSum is odd → impossible.
 *
 * * Otherwise:
 *        We just need to check
 *        if a subset exists with sum = totalSum / 2
 *
 * * This becomes a Subset Sum Problem.
 *
 * ---------------------------------------------------------------
 *
 * Example 1:
 *   nums = {1, 5, 11, 5}
 *
 *   totalSum = 22
 *   target = 11
 *
 *   Subset {11} or {5,5,1}
 *
 *   Answer = true
 *
 * ---------------------------------------------------------------
 *
 * Example 2:
 *   nums = {1, 2, 3, 5}
 *
 *   totalSum = 11 (odd)
 *
 *   Cannot split equally.
 *
 *   Answer = false
 *
 * ---------------------------------------------------------------
 *
 * Example 3:
 *   nums = {2, 2, 3, 5}
 *
 *   totalSum = 12
 *   target = 6
 *
 *   No subset forms 6.
 *
 *   Answer = false
 *
 * ===============================================================
 * Approach 1: Brute Force (Recursion)
 * ===============================================================
 *
 * * Try all subsets.
 * * At each index:
 *      - Take element
 *      - Skip element
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

bool BruteforceSolution(vector<int> &nums)
{
    int totalSum = accumulate(nums.begin(), nums.end(), 0);

    if (totalSum % 2 != 0)
        return false;

    int target = totalSum / 2;

    return solveRec(nums.size() - 1, target, nums);
}

/**
 * ===============================================================
 * Approach 2: Optimal (1D Dynamic Programming)
 * ===============================================================
 *
 * * dp[t] = true if subset forms sum t
 *
 * * Traverse elements.
 * * For each element, update dp backwards.
 *
 * Time Complexity:  O(n * target)
 * Space Complexity: O(target)
 */

bool OptimalSolution(vector<int> &nums)
{
    int totalSum = accumulate(nums.begin(), nums.end(), 0);

    if (totalSum % 2 != 0)
        return false;

    int target = totalSum / 2;

    vector<bool> dp(target + 1, false);

    dp[0] = true;

    for (int num : nums)
    {
        for (int t = target; t >= num; t--)
        {
            dp[t] = dp[t] || dp[t - num];
        }
    }

    return dp[target];
}

int main()
{
    vector<int> nums = {1, 5, 11, 5};

    // bool ans = BruteforceSolution(nums);
    bool ans = OptimalSolution(nums);

    cout << (ans ? "True" : "False");

    return 0;
}
