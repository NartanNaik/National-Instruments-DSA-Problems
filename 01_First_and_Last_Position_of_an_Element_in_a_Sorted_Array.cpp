#include <bits/stdc++.h>
using namespace std;

/**
 * searchRange
 *
 * * Finds the first and last occurrence of a target element
 *   inside a sorted array.
 *
 * ? Why sorted?
 *   Even though the array is sorted, this approach does NOT use that advantage.
 *
 * ! This is a brute force solution (not optimal for interviews).
 *
 * ---------------------------------------
 * Approach: Linear Scan (Brute Force)
 * ---------------------------------------
 *
 * * Traverse the entire array from left to right.
 * * When target is found:
 *      - If this is the first occurrence, store index in "first".
 *      - Always update "last" to current index.
 * * After traversal:
 *      - "first" holds first occurrence.
 *      - "last" holds last occurrence.
 *
 * ---------------------------------------
 * Time Complexity (TC):
 * ---------------------------------------
 * O(n)
 * Because we iterate through all n elements once.
 *
 * ---------------------------------------
 * Space Complexity (SC):
 * ---------------------------------------
 * O(1)
 * Only two extra integer variables are used.
 *
 * ---------------------------------------
 * Edge Case Handling:
 * ---------------------------------------
 * * If target does not exist → return {-1, -1}
 * * If target appears once → return {index, index}
 *
 * TODO:
 * Refactor using Binary Search to achieve O(log n)
 */

vector<int> BruteforceSolution(vector<int> &nums, int target)
{

    // * Initialize first and last occurrence indices.
    // * -1 indicates "not found".
    int first = -1, last = -1;

    // * Traverse the entire array from left to right.
    for (int i = 0; i < nums.size(); i++)
    {

        // * If current element matches the target
        if (nums[i] == target)
        {

            // ? Is this the first occurrence?
            // If first is still -1, we haven't recorded any index yet.
            if (first == -1)
                first = i; // Store first occurrence

            // * Update last occurrence every time target is found.
            // This ensures we always store the most recent index.
            last = i;
        }
    }

    // * Return the range of the target element.
    // If not found → both remain -1.
    return {first, last};
}

/**
 * Thought Process:
 *
 * * Since the array is sorted, we can use Binary Search utilities.
 *
 * * lower_bound(nums.begin(), nums.end(), target)
 *     → Gives iterator to first element >= target.
 *
 * * upper_bound(nums.begin(), nums.end(), target)
 *     → Gives iterator to first element > target.
 *
 * * If target exists:
 *     - First occurrence  = index of lower_bound
 *     - Last occurrence   = index of upper_bound - 1
 *
 * ? Why subtract 1 from upper_bound?
 *   Because upper_bound gives first element GREATER than target.
 *   So last occurrence is just before that.
 *
 * ! Important Check:
 *   If lower_bound points to end OR value != target,
 *   then target does not exist.
 *
 * ---------------------------------------
 * Time Complexity:  O(log n)
 * Space Complexity: O(1)
 */
vector<int> BetterSolution(vector<int> &nums, int target)
{

    // * Find first position where element >= target
    auto it1 = lower_bound(nums.begin(), nums.end(), target);

    // * Find first position where element > target
    auto it2 = upper_bound(nums.begin(), nums.end(), target);

    // * If iterator reached end OR value is not equal to target
    //   → target does not exist in array
    if (it1 == nums.end() || *it1 != target)
        return {-1, -1};

    // * Convert iterator to index
    int first = it1 - nums.begin();

    // * Subtract 1 because upper_bound gives next greater element
    int last = it2 - nums.begin() - 1;

    return {first, last};
}

/**
 * Thought Process (Optimal Binary Search Approach)
 *
 * * Since the array is sorted, we can use Binary Search.
 *
 * * Instead of stopping when we find the target,
 *   we continue searching:
 *      - Left side  → to find FIRST occurrence
 *      - Right side → to find LAST occurrence
 *
 * ? Why two separate functions?
 *   Because the boundary movement logic differs slightly.
 *
 * ---------------------------------------
 * Time Complexity:  O(log n)
 *   Each function performs binary search.
 *
 * Space Complexity: O(1)
 *   Only a few variables are used.
 *
 * ! Important:
 *   Works only for sorted arrays.
 */

/**
 * findFirst
 *
 * * Finds the first (leftmost) occurrence of target.
 *
 * Logic:
 * - If target found:
 *      store index
 *      move left (high = mid - 1)
 *   because there might be an earlier occurrence.
 */
int findFirst(vector<int> &nums, int target)
{

    int low = 0, high = nums.size() - 1;

    // * -1 means target not found yet
    int first = -1;

    while (low <= high)
    {

        // * Prevents overflow compared to (low + high) / 2
        int mid = low + (high - low) / 2;

        if (nums[mid] == target)
        {

            // * Store potential answer
            first = mid;

            // ? Why move left?
            // To check if there exists an earlier occurrence.
            high = mid - 1;
        }
        else if (nums[mid] < target)
        {

            // * Target must be on the right side
            low = mid + 1;
        }
        else
        {

            // * Target must be on the left side
            high = mid - 1;
        }
    }

    return first;
}

/**
 * findLast
 *
 * * Finds the last (rightmost) occurrence of target.
 *
 * Logic:
 * - If target found:
 *      store index
 *      move right (low = mid + 1)
 *   because there might be a later occurrence.
 */
int findLast(vector<int> &nums, int target)
{

    int low = 0, high = nums.size() - 1;

    int last = -1;

    while (low <= high)
    {

        int mid = low + (high - low) / 2;

        if (nums[mid] == target)
        {

            // * Store potential answer
            last = mid;

            // ? Why move right?
            // To check if there exists a later occurrence.
            low = mid + 1;
        }
        else if (nums[mid] < target)
        {

            low = mid + 1;
        }
        else
        {

            high = mid - 1;
        }
    }

    return last;
}

/**
 * searchRange
 *
 * * Combines both boundary searches.
 *
 * Steps:
 * 1. Find first occurrence.
 * 2. Find last occurrence.
 * 3. Return both as a range.
 */
vector<int> OptimalSolution(vector<int> &nums, int target)
{

    int first = findFirst(nums, target);
    int last = findLast(nums, target);

    return {first, last};
}

int main()
{
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    int target = 8;

    // vector<int> ans = BruteforceSolution(nums, target);
    // vector<int> ans = BetterSolution(nums, target);
    vector<int> ans = OptimalSolution(nums, target);

    cout << ans[0] << " " << ans[1];
    return 0;
}