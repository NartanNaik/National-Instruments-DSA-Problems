#include <bits/stdc++.h>
using namespace std;

/**
 * Find Minimum in Rotated Sorted Array
 *
 * * Given a sorted array that has been rotated at some pivot,
 *   return the minimum element.
 *
 * Example:
 *   Original: [1 2 3 4 5]
 *   Rotated : [4 5 1 2 3]
 *   Minimum = 1
 *
 * ! No duplicate elements assumed.
 *
 * ===============================================================
 * Approach 1: Brute Force (Linear Scan)
 * ===============================================================
 *
 * * Traverse the array.
 * * Track minimum value.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */

int BruteforceSolution(vector<int> &nums)
{
    int mini = nums[0];

    for (int i = 1; i < nums.size(); i++)
    {
        mini = min(mini, nums[i]);
    }

    return mini;
}

/**
 * ===============================================================
 * Approach 2: Optimal (Binary Search)
 * ===============================================================
 *
 * * Key Observation:
 *   In a rotated sorted array:
 *      - One half is always sorted.
 *
 * * If entire range is already sorted:
 *      nums[low] <= nums[high]
 *      → nums[low] is minimum.
 *
 * * Otherwise:
 *      Compare nums[mid] with nums[high]
 *
 *      If nums[mid] > nums[high]
 *         → Minimum is in RIGHT half
 *
 *      Else
 *         → Minimum is in LEFT half (including mid)
 *
 * Time Complexity:  O(log n)
 * Space Complexity: O(1)
 *
 * ! Classic binary search variant.
 */

int OptimalSolution(vector<int> &nums)
{
    int low = 0;
    int high = nums.size() - 1;

    while (low < high)
    {
        // * If already sorted
        if (nums[low] <= nums[high])
            return nums[low];

        int mid = low + (high - low) / 2;

        // * If mid element is greater than high,
        //   minimum must be in right half
        if (nums[mid] > nums[high])
        {
            low = mid + 1;
        }
        else
        {
            // * Minimum is in left half (including mid)
            high = mid;
        }
    }

    // * When low == high → minimum found
    return nums[low];
}

int main()
{
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};

    // int ans = BruteforceSolution(nums);
    int ans = OptimalSolution(nums);

    cout << ans;

    return 0;
}