#include <bits/stdc++.h>
using namespace std;

/**
 * Coin Change (Minimum Number of Coins)
 *
 * * Given:
 *      - coins[] → denominations
 *      - amount  → target amount
 *
 * * Return the minimum number of coins required to make the amount.
 * * If not possible → return -1.
 *
 * ! You can use unlimited copies of each coin.
 *
 * ===============================================================
 * Example 1:
 *   coins = {1, 2, 5}
 *   amount = 11
 *
 *   Best choice:
 *      5 + 5 + 1 = 11
 *
 *   Answer = 3
 *
 * ---------------------------------------------------------------
 *
 * Example 2:
 *   coins = {2}
 *   amount = 3
 *
 *   Not possible to form 3 using 2
 *
 *   Answer = -1
 *
 * ---------------------------------------------------------------
 *
 * Example 3:
 *   coins = {1, 3, 4}
 *   amount = 6
 *
 *   Best choice:
 *      3 + 3 = 6
 *
 *   Answer = 2
 *
 * ===============================================================
 * Approach 1: Brute Force (Recursion)
 * ===============================================================
 *
 * * At each coin:
 *      - Take coin (stay at same index because unlimited supply)
 *      - Skip coin (move to next index)
 *
 * Time Complexity:  Exponential
 * Space Complexity: O(amount)
 */

int solveRec(int index, int amount, vector<int> &coins)
{
    if (index == 0)
    {
        if (amount % coins[0] == 0)
            return amount / coins[0];
        else
            return 1e9; // large number (impossible case)
    }

    int notTake = solveRec(index - 1, amount, coins);

    int take = 1e9;
    if (coins[index] <= amount)
        take = 1 + solveRec(index, amount - coins[index], coins);

    return min(take, notTake);
}

int BruteforceSolution(vector<int> &coins, int amount)
{
    int n = coins.size();
    int ans = solveRec(n - 1, amount, coins);

    return (ans >= 1e9) ? -1 : ans;
}

/**
 * ===============================================================
 * Approach 2: Better (DP - Tabulation)
 * ===============================================================
 *
 * * dp[i][a] =
 *      minimum coins needed using coins[0..i] to make amount a
 *
 * Transition:
 *      Not Take → dp[i-1][a]
 *      Take     → 1 + dp[i][a - coins[i]]
 *
 * Time Complexity:  O(n * amount)
 * Space Complexity: O(n * amount)
 */

int BetterSolution(vector<int> &coins, int amount)
{
    int n = coins.size();

    vector<vector<int>> dp(n, vector<int>(amount + 1, 1e9));

    for (int a = 0; a <= amount; a++)
    {
        if (a % coins[0] == 0)
            dp[0][a] = a / coins[0];
    }

    for (int i = 1; i < n; i++)
    {
        for (int a = 0; a <= amount; a++)
        {
            int notTake = dp[i - 1][a];

            int take = 1e9;
            if (coins[i] <= a)
                take = 1 + dp[i][a - coins[i]];

            dp[i][a] = min(take, notTake);
        }
    }

    int ans = dp[n - 1][amount];
    return (ans >= 1e9) ? -1 : ans;
}

/**
 * ===============================================================
 * Approach 3: Optimal (1D DP)
 * ===============================================================
 *
 * * dp[a] =
 *      minimum coins required to make amount a
 *
 * * For each coin:
 *      update dp from coin value to amount
 *
 * Time Complexity:  O(n * amount)
 * Space Complexity: O(amount)
 */

int OptimalSolution(vector<int> &coins, int amount)
{
    vector<int> dp(amount + 1, 1e9);

    dp[0] = 0;

    for (int coin : coins)
    {
        for (int a = coin; a <= amount; a++)
        {
            dp[a] = min(dp[a], 1 + dp[a - coin]);
        }
    }

    return (dp[amount] >= 1e9) ? -1 : dp[amount];
}

int main()
{
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    // int ans = BruteforceSolution(coins, amount);
    // int ans = BetterSolution(coins, amount);
    int ans = OptimalSolution(coins, amount);

    cout << ans;

    return 0;
}
