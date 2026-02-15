#include <bits/stdc++.h>
using namespace std;

/**
 * Square Root of an Integer (Using Binary Search)
 *
 * * Given a non-negative integer x,
 *   return the floor value of its square root.
 *
 * ? Floor value means:
 *   sqrt(8) = 2.828...
 *   Answer = 2
 *
 * ! We are NOT allowed to use built-in sqrt().
 *
 * ===============================================================
 * Approach 1: Brute Force (Linear Search)
 * ===============================================================
 *
 * * Start from 1 and keep squaring numbers.
 * * Stop when square exceeds x.
 *
 * Time Complexity:  O(√x)
 * Space Complexity: O(1)
 */

int BruteforceSolution(int x)
{
    if (x == 0 || x == 1)
        return x;

    int i = 1;

    // * Keep increasing i until i*i exceeds x
    while ((long long)i * i <= x)
        i++;

    // * When loop stops, i*i just exceeded x
    return i - 1;
}

/**
 * ===============================================================
 * Approach 2: Optimal (Binary Search)
 * ===============================================================
 *
 * * Search space: 1 to x
 * * We try to find the largest number whose square <= x.
 *
 * Binary Search Logic:
 *   mid * mid == x → exact sqrt
 *   mid * mid < x  → move right (store mid as potential answer)
 *   mid * mid > x  → move left
 *
 * ? Why store answer?
 *   Because we need floor value when exact square not found.
 *
 * Time Complexity:  O(log x)
 * Space Complexity: O(1)
 */

int OptimalSolution(int x)
{
    if (x == 0 || x == 1)
        return x;

    long long low = 1, high = x;
    int ans = 0;

    while (low <= high)
    {
        long long mid = low + (high - low) / 2;

        long long square = mid * mid;

        if (square == x)
        {
            return mid; // * Perfect square
        }
        else if (square < x)
        {
            // * mid is a possible answer
            ans = mid;

            // * Try to find a bigger valid square
            low = mid + 1;
        }
        else
        {
            // * Square too large, move left
            high = mid - 1;
        }
    }

    // * Return floor value
    return ans;
}

int main()
{
    int x = 8;

    // int ans = BruteforceSolution(x);
    int ans = OptimalSolution(x);

    cout << ans;

    return 0;
}