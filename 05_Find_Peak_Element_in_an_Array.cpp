#include <bits/stdc++.h>
using namespace std;

/**
 * Find Peak Element in an Array
 *
 * * A peak element is an element that is strictly greater than its neighbors.
 *
 *   nums[i] is peak if:
 *      nums[i] > nums[i-1]  AND  nums[i] > nums[i+1]
 *
 * * For boundary elements:
 *      First element is peak if nums[0] > nums[1]
 *      Last element  is peak if nums[n-1] > nums[n-2]
 *
 * ! There is always at least one peak.
 *
 * ===============================================================
 * Approach 1: Brute Force (Linear Scan)
 * ===============================================================
 *
 * * Traverse the array.
 * * For every index check left and right neighbor.
 * * Return the first index satisfying peak condition.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */

int BruteforceSolution(vector<int> &nums)
{
    int n = nums.size();

    for (int i = 0; i < n; i++)
    {
        bool left  = (i == 0) || (nums[i] > nums[i - 1]);
        bool right = (i == n - 1) || (nums[i] > nums[i + 1]);

        // * If both conditions satisfied → peak found
        if (left && right)
            return i;
    }

    return -1; // * Should never reach here (guaranteed peak)
}

/**
 * ===============================================================
 * Approach 2: Optimal (Binary Search)
 * ===============================================================
 *
 * * Key Observation:
 *   If nums[mid] < nums[mid + 1]
 *      → A peak must exist on the right side.
 *
 *   If nums[mid] > nums[mid + 1]
 *      → A peak exists on the left side (including mid).
 *
 * ? Why does this work?
 *   Because the array behaves like a mountain:
 *   - If slope goes up → peak is ahead.
 *   - If slope goes down → peak is behind.
 *
 * * We don't need full sorted property.
 *   Just compare adjacent elements.
 *
 * Time Complexity:  O(log n)
 * Space Complexity: O(1)
 */

int OptimalSolution(vector<int> &nums)
{
    int low = 0, high = nums.size() - 1;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        // * If mid element is smaller than next
        //   → slope is rising → peak on right side
        if (nums[mid] < nums[mid + 1])
        {
            low = mid + 1;
        }
        else
        {
            // * Slope is falling
            //   → peak is at mid or on left side
            high = mid;
        }
    }

    // * When low == high → peak index
    return low;
}

int main()
{
    vector<int> nums = {1, 2, 3, 1};

    // int ans = BruteforceSolution(nums);
    int ans = OptimalSolution(nums);

    cout << ans;

    return 0;
}
