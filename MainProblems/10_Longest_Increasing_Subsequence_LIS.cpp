#include <bits/stdc++.h>
using namespace std;

/**
 * Longest Increasing Subsequence (LIS)
 *
 * * Given an array of integers,
 *   find the length of the longest strictly increasing subsequence.
 *
 * ? Subsequence:
 *   - Elements are taken in order
 *   - Not necessarily contiguous
 *
 * Example:
 *   nums = {10, 9, 2, 5, 3, 7, 101, 18}
 *   LIS  = {2, 3, 7, 101}
 *   Answer = 4
 *   
 *   next element > previous element <- thi is the thing!
 * 
 * ===============================================================
 * Approach 1: Brute Force (Recursion - Try All Subsequences)
 * ===============================================================
 *
 * * At every index:
 *      - Take the element (if increasing)
 *      - Or skip it
 *
 * * Exponential combinations explored.
 *
 * Time Complexity:  O(2^n)
 * Space Complexity: O(n) recursion stack
 *
 * ! Not feasible for large n.
 */

int solveRec(int index, int prevIndex, vector<int> &nums)
{
    if (index == nums.size())
        return 0;

    // * Option 1: Skip current element
    int notTake = solveRec(index + 1, prevIndex, nums);

    // * Option 2: Take current element (if valid)
    int take = 0;
    if (prevIndex == -1 || nums[index] > nums[prevIndex])
    {
        take = 1 + solveRec(index + 1, index, nums);
    }

    return max(take, notTake);
}

int BruteforceSolution(vector<int> &nums)
{
    return solveRec(0, -1, nums);
}

/**
 * ===============================================================
 * Approach 2: Better (Dynamic Programming - O(n^2))
 * ===============================================================
 *
 * * dp[i] = length of LIS ending at index i
 *
 * For each i:
 *   check all j < i
 *   if nums[j] < nums[i]
 *      dp[i] = max(dp[i], dp[j] + 1)
 *
 * Time Complexity:  O(n^2)
 * Space Complexity: O(n)
 */

int BetterSolution(vector<int> &nums)
{
    int n = nums.size();

    vector<int> dp(n, 1);  // * Minimum LIS length at each index is 1

    int ans = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            // * If increasing
            if (nums[j] < nums[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        ans = max(ans, dp[i]);
    }

    return ans;
}

/**
 * ===============================================================
 * Approach 3: Optimal (Binary Search + Greedy - O(n log n))
 * ===============================================================
 *
 * * Maintain a temporary array 'tails'.
 *
 * tails[k] = smallest possible tail of an increasing subsequence
 *            of length (k + 1)
 *
 * * For each number:
 *      - Find lower_bound position in tails
 *      - Replace element
 *      - If beyond last → push back
 *
 * ? Why lower_bound?
 *   To keep tails sorted and minimal.
 *
 * ! Important:
 *   tails does NOT store actual LIS,
 *   but its size gives correct length.
 *
 * Time Complexity:  O(n log n)
 * Space Complexity: O(n)
 */

int OptimalSolution(vector<int> &nums)
{
    vector<int> tails;

    for (int num : nums)
    {
        // * Find position to replace
        auto it = lower_bound(tails.begin(), tails.end(), num);

        if (it == tails.end())
        {
            // * Extend LIS
            tails.push_back(num);
        }
        else
        {
            // * Replace to maintain smaller tail
            *it = num;
        }
    }

    return tails.size();
}

int main()
{
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    // int ans = BruteforceSolution(nums);
    // int ans = BetterSolution(nums);
    int ans = OptimalSolution(nums);

    cout << ans;

    return 0;
}
