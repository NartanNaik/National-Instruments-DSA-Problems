#include <bits/stdc++.h>
using namespace std;

/**
 * Aggressive Cows (Maximum Minimum Distance)
 *
 * * We are given:
 *      - stalls[] → positions of stalls (unsorted)
 *      - k        → number of cows
 *
 * * We must place k cows in stalls such that:
 *      The minimum distance between any two cows is maximized.
 *
 * ! Classic "Binary Search on Answer" problem.
 *
 * ===============================================================
 * Approach 1: Brute Force
 * ===============================================================
 *
 * * Sort stall positions.
 * * Try all possible distances from 1 to (max - min).
 * * For each distance:
 *      - Try placing cows greedily.
 *      - If possible, update answer.
 *
 * Time Complexity:  O((maxDist) * n)
 * Space Complexity: O(1)
 *
 * ! Very inefficient for large constraints.
 */

bool canPlace(vector<int> &stalls, int k, int dist)
{
    int cows = 1; // * Place first cow at first stall
    int lastPos = stalls[0];

    for (int i = 1; i < stalls.size(); i++)
    {
        // * If current stall is at least 'dist' away
        if (stalls[i] - lastPos >= dist)
        {
            cows++;
            lastPos = stalls[i];

            if (cows == k)
                return true;
        }
    }

    return false;
}

int BruteforceSolution(vector<int> &stalls, int k)
{
    sort(stalls.begin(), stalls.end());

    int n = stalls.size();
    int maxDist = stalls[n - 1] - stalls[0];

    int ans = 0;

    for (int d = 1; d <= maxDist; d++)
    {
        if (canPlace(stalls, k, d))
            ans = d;
    }

    return ans;
}

/**
 * ===============================================================
 * Approach 2: Optimal (Binary Search on Answer)
 * ===============================================================
 *
 * * Observation:
 *   If we can place cows with distance 'd',
 *   then we can also place them with any smaller distance.
 *
 *   → Monotonic behavior → Binary Search applicable.
 *
 * * Search space:
 *      low  = 1
 *      high = stalls[n-1] - stalls[0]
 *
 * * For mid distance:
 *      - If possible → try bigger distance (move right)
 *      - Else → reduce distance (move left)
 *
 * Time Complexity:  O(n log(maxDist))
 * Space Complexity: O(1)
 */

int OptimalSolution(vector<int> &stalls, int k)
{
    sort(stalls.begin(), stalls.end());

    int low = 1;
    int high = stalls.back() - stalls.front();

    int ans = 0;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (canPlace(stalls, k, mid))
        {
            // * Distance possible → try larger
            ans = mid;
            low = mid + 1;
        }
        else
        {
            // * Distance too large → reduce
            high = mid - 1;
        }
    }

    return ans;
}

int main()
{
    vector<int> stalls = {1, 2, 4, 8, 9};
    int k = 3;

    // int ans = BruteforceSolution(stalls, k);
    int ans = OptimalSolution(stalls, k);

    cout << ans;

    return 0;
}