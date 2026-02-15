#include <bits/stdc++.h>
using namespace std;

/**
 * Maximum Product Subarray
 *
 * * Given an integer array nums,
 *   find the contiguous subarray
 *   that has the largest product.
 *
 * ---------------------------------------------------------------
 * Key Idea:
 *
 * * Unlike Maximum Sum Subarray,
 *   product behaves differently because:
 *
 *      - Negative × Negative = Positive
 *      - Zero resets product
 *
 * * So at every index, we must track:
 *
 *      1️⃣ Maximum product ending at current index
 *      2️⃣ Minimum product ending at current index
 *
 * * Why minimum?
 *      Because a negative minimum can become
 *      a large positive when multiplied
 *      with another negative number.
 *
 * ---------------------------------------------------------------
 *
 * Example 1:
 *   nums = {2, 3, -2, 4}
 *
 *   Maximum product subarray = {2, 3}
 *
 *   Answer = 6
 *
 * ---------------------------------------------------------------
 *
 * Example 2:
 *   nums = {-2, 0, -1}
 *
 *   Maximum product = 0
 *
 *   Answer = 0
 *
 * ---------------------------------------------------------------
 *
 * Example 3:
 *   nums = {-2, 3, -4}
 *
 *   Subarray = {-2, 3, -4}
 *
 *   Product = 24
 *
 *   Answer = 24
 *
 * ===============================================================
 * Approach 1: Brute Force
 * ===============================================================
 *
 * * Try all possible subarrays.
 * * Compute product of each.
 * * Track maximum.
 *
 * Time Complexity:  O(n^2)
 * Space Complexity: O(1)
 */

int BruteforceSolution(vector<int> &nums)
{
    int n = nums.size();
    int maxi = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        int prod = 1;

        for (int j = i; j < n; j++)
        {
            prod *= nums[j];
            maxi = max(maxi, prod);
        }
    }

    return maxi;
}

/**
 * ===============================================================
 * Approach 2: Optimal (Kadane Variant)
 * ===============================================================
 *
 * * Maintain:
 *      currMax → max product ending here
 *      currMin → min product ending here
 *
 * * If current number is negative,
 *   swap currMax and currMin.
 *
 * * Update:
 *      currMax = max(num, currMax * num)
 *      currMin = min(num, currMin * num)
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */

int OptimalSolution(vector<int> &nums)
{
    int n = nums.size();

    int currMax = nums[0];
    int currMin = nums[0];
    int ans = nums[0];

    for (int i = 1; i < n; i++)
    {
        // * If current element is negative,
        //   swap max and min
        if (nums[i] < 0)
            swap(currMax, currMin);

        // * Update current max product
        currMax = max(nums[i], currMax * nums[i]);

        // * Update current min product
        currMin = min(nums[i], currMin * nums[i]);

        // * Update global answer
        ans = max(ans, currMax);
    }

    return ans;
}

int main()
{
    vector<int> nums = {2, 3, -2, 4};

    // int ans = BruteforceSolution(nums);
    int ans = OptimalSolution(nums);

    cout << ans;

    return 0;
}
