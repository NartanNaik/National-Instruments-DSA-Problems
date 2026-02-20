#include <bits/stdc++.h>
using namespace std;

/**
 * Edit Distance (Convert String A to String B)
 *
 * * Given two strings word1 and word2,
 *   find the minimum number of operations required
 *   to convert word1 into word2.
 *
 * Allowed Operations:
 *   1. Insert a character
 *   2. Delete a character
 *   3. Replace a character
 *
 * Example:
 *   word1 = "horse"
 *   word2 = "ros"
 *
 *   horse → rorse  (replace h → r)
 *   rorse → rose   (delete r)
 *   rose  → ros    (delete e)
 *
 *   Answer = 3
 *
 * ===============================================================
 * Approach 1: Brute Force (Recursion)
 * ===============================================================
 *
 * * If characters match → move both pointers
 * * Else try:
 *      - Insert
 *      - Delete
 *      - Replace
 *
 * * Take minimum of all.
 *
 * Time Complexity:  O(3^(n+m))
 * Space Complexity: O(n+m) recursion stack
 */

int solveRec(int i, int j, string &s1, string &s2)
{
    // * If s1 exhausted → need to insert remaining chars of s2
    if (i < 0)
        return j + 1;

    // * If s2 exhausted → need to delete remaining chars of s1
    if (j < 0)
        return i + 1;

    // * If characters match
    if (s1[i] == s2[j])
        return solveRec(i - 1, j - 1, s1, s2);

    // * Try all 3 operations
    int insertOp  = 1 + solveRec(i, j - 1, s1, s2);
    int deleteOp  = 1 + solveRec(i - 1, j, s1, s2);
    int replaceOp = 1 + solveRec(i - 1, j - 1, s1, s2);

    return min({insertOp, deleteOp, replaceOp});
}

int BruteforceSolution(string s1, string s2)
{
    return solveRec(s1.size() - 1, s2.size() - 1, s1, s2);
}

/**
 * ===============================================================
 * Approach 2: Better (DP - Tabulation)
 * ===============================================================
 *
 * * dp[i][j] =
 *      Minimum operations to convert
 *      s1[0..i-1] → s2[0..j-1]
 *
 * Base Cases:
 *   dp[i][0] = i  (delete all characters)
 *   dp[0][j] = j  (insert all characters)
 *
 * Transition:
 *   If match:
 *      dp[i][j] = dp[i-1][j-1]
 *   Else:
 *      1 + min(
 *          dp[i][j-1],   // insert
 *          dp[i-1][j],   // delete
 *          dp[i-1][j-1]  // replace
 *      )
 *
 * Time Complexity:  O(n * m)
 * Space Complexity: O(n * m)
 */

int BetterSolution(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; i++)
        dp[i][0] = i;

    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min({
                    dp[i][j - 1],     // insert
                    dp[i - 1][j],     // delete
                    dp[i - 1][j - 1]  // replace
                });
            }
        }
    }

    return dp[n][m];
}

/**
 * ===============================================================
 * Approach 3: Optimal (Space Optimized DP)
 * ===============================================================
 *
 * * Since dp[i][j] depends only on previous row,
 *   we can optimize to 2 rows.
 *
 * Time Complexity:  O(n * m)
 * Space Complexity: O(m)
 */

int OptimalSolution(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();

    vector<int> prev(m + 1), curr(m + 1);

    for (int j = 0; j <= m; j++)
        prev[j] = j;

    for (int i = 1; i <= n; i++)
    {
        curr[0] = i;

        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = prev[j - 1];
            }
            else
            {
                curr[j] = 1 + min({
                    curr[j - 1],     // insert
                    prev[j],         // delete
                    prev[j - 1]      // replace
                });
            }
        }

        prev = curr;
    }

    return prev[m];
}

int main()
{
    string s1 = "horse";
    string s2 = "ros";

    // int ans = BruteforceSolution(s1, s2);
    // int ans = BetterSolution(s1, s2);
    int ans = OptimalSolution(s1, s2);

    cout << ans;

    return 0;
}
