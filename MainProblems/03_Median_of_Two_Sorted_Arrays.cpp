#include <bits/stdc++.h>
using namespace std;

/**
 * Median of Two Sorted Arrays
 *
 * * Given two sorted arrays nums1 and nums2,
 *   return the median of the combined sorted array.
 *
 * ? Median:
 *   - If total elements is odd  → middle element
 *   - If total elements is even → average of two middle elements
 *
 * ! Arrays are individually sorted.
 *
 * ===============================================================
 * Approach 1: Brute Force (Merge + Sort)
 * ===============================================================
 *
 * * Merge both arrays into one vector.
 * * Sort the merged array.
 * * Compute median.
 *
 * Time Complexity:  O((n+m) log(n+m))
 * Space Complexity: O(n+m)
 */

double BruteforceSolution(vector<int> &nums1, vector<int> &nums2)
{
    vector<int> merged;

    // * Insert both arrays
    merged.insert(merged.end(), nums1.begin(), nums1.end());
    merged.insert(merged.end(), nums2.begin(), nums2.end());

    // * Sort the merged array
    sort(merged.begin(), merged.end());

    int n = merged.size();

    // * If odd length → single middle
    if (n % 2 == 1)
        return merged[n / 2];

    // * If even length → average of two middles
    return (merged[n / 2] + merged[n / 2 - 1]) / 2.0;
}

/**
 * ===============================================================
 * Approach 2: Better (Merge Like Merge Sort - No Extra Sorting)
 * ===============================================================
 *
 * * Since arrays are already sorted,
 *   we can merge them using two pointers.
 * * Stop once we reach median position.
 *
 * Time Complexity:  O(n + m)
 * Space Complexity: O(n + m)
 */

double BetterSolution(vector<int> &nums1, vector<int> &nums2)
{
    int n1 = nums1.size(), n2 = nums2.size();
    vector<int> merged;

    int i = 0, j = 0;

    // * Merge process
    while (i < n1 && j < n2)
    {
        if (nums1[i] <= nums2[j])
            merged.push_back(nums1[i++]);
        else
            merged.push_back(nums2[j++]);
    }

    // * Add remaining elements
    while (i < n1)
        merged.push_back(nums1[i++]);

    while (j < n2)
        merged.push_back(nums2[j++]);

    int n = merged.size();

    if (n % 2 == 1)
        return merged[n / 2];

    return (merged[n / 2] + merged[n / 2 - 1]) / 2.0;
}

/**
 * ===============================================================
 * Approach 3: Optimal (Binary Search on Smaller Array)
 * ===============================================================
 *
 * * Instead of merging, we partition both arrays.
 *
 * Goal:
 *   Divide both arrays such that:
 *   - Left half contains half of total elements
 *   - All elements in left half <= right half
 *
 * Key Idea:
 *   Perform binary search on smaller array.
 *
 * Let:
 *   cut1 = partition in nums1
 *   cut2 = partition in nums2
 *
 * Conditions:
 *   maxLeft1 <= minRight2
 *   maxLeft2 <= minRight1
 *
 * If satisfied → correct partition found.
 *
 * Time Complexity:  O(log(min(n1, n2)))
 * Space Complexity: O(1)
 *
 * ! This is the expected interview solution.
 */

double OptimalSolution(vector<int> &nums1, vector<int> &nums2)
{
    // * Ensure nums1 is smaller
    if (nums1.size() > nums2.size())
        return OptimalSolution(nums2, nums1);

    int n1 = nums1.size();
    int n2 = nums2.size();

    int low = 0, high = n1;

    while (low <= high)
    {
        int cut1 = (low + high) / 2;
        int cut2 = (n1 + n2 + 1) / 2 - cut1;

        int left1  = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
        int right1 = (cut1 == n1) ? INT_MAX : nums1[cut1];

        int left2  = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
        int right2 = (cut2 == n2) ? INT_MAX : nums2[cut2];

        // * Correct partition condition
        if (left1 <= right2 && left2 <= right1)
        {
            // * If total length is odd
            if ((n1 + n2) % 2 == 1)
                return max(left1, left2);

            // * If even
            return (max(left1, left2) + min(right1, right2)) / 2.0;
        }
        else if (left1 > right2)
        {
            // * Move left in nums1
            high = cut1 - 1;
        }
        else
        {
            // * Move right in nums1
            low = cut1 + 1;
        }
    }

    return 0.0; // * Should never reach here
}

int main()
{
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};

    // double ans = BruteforceSolution(nums1, nums2);
    // double ans = BetterSolution(nums1, nums2);
    double ans = OptimalSolution(nums1, nums2);

    cout << ans;

    return 0;
}
