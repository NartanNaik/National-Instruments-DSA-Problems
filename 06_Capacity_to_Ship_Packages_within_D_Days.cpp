#include <bits/stdc++.h>
using namespace std;

/**
 * Capacity to Ship Packages Within D Days
 *
 * * We are given:
 *      - weights[] → weight of packages (must ship in given order)
 *      - D         → number of days
 *
 * * We must find the MINIMUM ship capacity so that
 *   all packages are shipped within D days.
 *
 * ! Packages must be shipped in order.
 * ! We cannot rearrange weights.
 *
 * ===============================================================
 * Approach 1: Brute Force (Try All Capacities)
 * ===============================================================
 *
 * * Capacity range:
 *      Minimum possible capacity = max(weights)
 *      Maximum possible capacity = sum(weights)
 *
 * * For each capacity in this range:
 *      - Simulate shipping process.
 *      - Count days required.
 *      - Return first capacity that works.
 *
 * Time Complexity:  O((sum - max) * n)
 * Space Complexity: O(1)
 *
 * ! Very inefficient for large inputs.
 */

int daysRequired(vector<int> &weights, int capacity)
{
    int days = 1;
    int load = 0;

    for (int w : weights)
    {
        // * If adding current weight exceeds capacity
        if (load + w > capacity)
        {
            days++;
            load = w;
        }
        else
        {
            load += w;
        }
    }

    return days;
}

int BruteforceSolution(vector<int> &weights, int D)
{
    int maxWeight = *max_element(weights.begin(), weights.end());
    int totalSum  = accumulate(weights.begin(), weights.end(), 0);

    for (int cap = maxWeight; cap <= totalSum; cap++)
    {
        if (daysRequired(weights, cap) <= D)
            return cap;
    }

    return -1;
}

/**
 * ===============================================================
 * Approach 2: Optimal (Binary Search on Answer)
 * ===============================================================
 *
 * * Observation:
 *   If capacity works → any larger capacity will also work.
 *   (Monotonic property)
 *
 *   So we can binary search on capacity.
 *
 * * Search space:
 *      low  = max(weights)
 *      high = sum(weights)
 *
 * * For mid capacity:
 *      - Calculate required days.
 *      - If days <= D → try smaller capacity (move left).
 *      - Else → increase capacity (move right).
 *
 * Time Complexity:  O(n * log(sum))
 * Space Complexity: O(1)
 *
 * ! Classic "Binary Search on Answer" problem.
 */

int OptimalSolution(vector<int> &weights, int D)
{
    int low  = *max_element(weights.begin(), weights.end());
    int high = accumulate(weights.begin(), weights.end(), 0);

    int ans = high;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        int requiredDays = daysRequired(weights, mid);

        if (requiredDays <= D)
        {
            // * Capacity works
            ans = mid;

            // ? Try smaller capacity
            high = mid - 1;
        }
        else
        {
            // * Capacity too small
            low = mid + 1;
        }
    }

    return ans;
}

int main()
{
    vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int D = 5;

    // int ans = BruteforceSolution(weights, D);
    int ans = OptimalSolution(weights, D);

    cout << ans;

    return 0;
}