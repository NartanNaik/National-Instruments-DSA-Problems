#include <bits/stdc++.h>
using namespace std;

/**
 * Longest Common Subsequence (LCS)
 *
 * * Given two strings text1 and text2,
 *   find the length of their Longest Common Subsequence.
 *
 * ? Subsequence:
 *   - Characters must appear in same relative order
 *   - Not necessarily contiguous
 *
 * Example:
 *   text1 = "abcde"
 *   text2 = "ace"
 *
 *   LCS = "ace"
 *   Answer = 3
 * 
 *   text1 = "AGGTAB"
 *   text2 = "GXTXAYB"
 *
 *   LCS = "GTAB"
 *   Answer = 4
 *
 *   text1 = "abc"
 *   text2 = "def"
 *
 *   LCS = ""
 *   Answer = 0
 *
 *
 * ===============================================================
 * Approach 1: Brute Force (Recursion)
 * ===============================================================
 *
 * * If characters match:
 *      1 + solve(i-1, j-1)
 *
 * * Else:
 *      max(
 *          solve(i-1, j),
 *          solve(i, j-1)
 *      )
 *
 * Time Complexity:  O(2^(n+m))
 * Space Complexity: O(n+m)
 */

int solveRec(int i, int j, string &s1, string &s2)
{
    if (i < 0 || j < 0)
        return 0;

    if (s1[i] == s2[j])
        return 1 + solveRec(i - 1, j - 1, s1, s2);

    return max(
        solveRec(i - 1, j, s1, s2),
        solveRec(i, j - 1, s1, s2)
    );
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
 *      LCS length of
 *      s1[0..i-1] and s2[0..j-1]
 *
 * Base:
 *   dp[i][0] = 0
 *   dp[0][j] = 0
 *
 * Transition:
 *   If match:
 *      dp[i][j] = 1 + dp[i-1][j-1]
 *   Else:
 *      dp[i][j] = max(
 *          dp[i-1][j],
 *          dp[i][j-1]
 *      )
 *
 * Time Complexity:  O(n * m)
 * Space Complexity: O(n * m)
 */

int BetterSolution(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(
                    dp[i - 1][j],
                    dp[i][j - 1]
                );
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
 *   we can reduce 2D → 1D.
 *
 * Time Complexity:  O(n * m)
 * Space Complexity: O(m)
 */

int OptimalSolution(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = 1 + prev[j - 1];
            }
            else
            {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }

        prev = curr;
    }

    return prev[m];
}

int main()
{
    string text1 = "abcde";
    string text2 = "ace";

    // int ans = BruteforceSolution(text1, text2);
    // int ans = BetterSolution(text1, text2);
    int ans = OptimalSolution(text1, text2);

    cout << ans;

    return 0;
}
