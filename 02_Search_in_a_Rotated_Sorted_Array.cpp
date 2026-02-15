#include <bits/stdc++.h>
using namespace std;

/**
 * Search in a Rotated Sorted Array
 *
 * * Given a sorted array that has been rotated at some pivot,
 *   search for a target element.
 *
 * ? What is a rotated array?
 *   Example:
 *   Original:  [1 2 3 4 5 6 7]
 *   Rotated:   [4 5 6 7 1 2 3]
 *
 * * The array is still partially sorted.
 *   At least one half (left or right) is always sorted.
 *
 * ! Important:
 *   No duplicate elements are assumed.
 *
 * ---------------------------------------
 * Approach 1: Brute Force (Linear Search)
 * ---------------------------------------
 *
 * * Simply traverse the array.
 * * If element matches target → return index.
 * *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */

int BruteforceSolution(vector<int> &nums, int target)
{
    // * Traverse entire array
    for (int i = 0; i < nums.size(); i++)
    {
        // * If target found → return index
        if (nums[i] == target)
            return i;
    }

    // * If not found
    return -1;
}

/**
 * ---------------------------------------
 * Approach 2: Optimal (Modified Binary Search)
 * ---------------------------------------
 *
 * * Since the array is rotated but originally sorted,
 *   at least one half is always sorted.
 *
 * * At each step:
 *   1. Find mid
 *   2. Check which half is sorted
 *   3. Decide whether target lies in sorted half
 *   4. Discard the other half
 *
 * ? Key Insight:
 *   If nums[low] <= nums[mid]
 *      → Left half is sorted
 *   Else
 *      → Right half is sorted
 *
 * Time Complexity:  O(log n)
 * Space Complexity: O(1)
 */

int OptimalSolution(vector<int> &nums, int target)
{
    int low = 0, high = nums.size() - 1;

    while (low <= high)
    {
        // * Safe mid calculation (avoids overflow)
        int mid = low + (high - low) / 2;

        // * If mid itself is target
        if (nums[mid] == target)
            return mid;

        // * Check if LEFT half is sorted
        if (nums[low] <= nums[mid])
        {
            // ? Is target inside left sorted half?
            if (nums[low] <= target && target < nums[mid])
            {
                // * Narrow search to left half
                high = mid - 1;
            }
            else
            {
                // * Search in right half
                low = mid + 1;
            }
        }
        else
        {
            // * Otherwise RIGHT half must be sorted
            if (nums[mid] < target && target <= nums[high])
            {
                // * Narrow search to right half
                low = mid + 1;
            }
            else
            {
                // * Search in left half
                high = mid - 1;
            }
        }
    }

    // * If target not found
    return -1;
}

int main()
{
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;

    int ans = BruteforceSolution(nums, target);
    // int ans = OptimalSolution(nums, target);

    cout << ans;

    return 0;
}
