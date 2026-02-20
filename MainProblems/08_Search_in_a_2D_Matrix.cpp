#include <bits/stdc++.h>
using namespace std;

/**
 * Search in a 2D Matrix
 *
 * * Given a matrix where:
 *      - Each row is sorted in ascending order.
 *      - First element of each row is greater than last element of previous row.
 *
 * * We must determine if a target exists in the matrix.
 *
 * ? Important Observation:
 *   The matrix behaves like a single sorted 1D array.
 *
 * Example:
 *   1  3  5
 *   7  9 11
 *
 *   Can be viewed as:
 *   [1 3 5 7 9 11]
 *
 * ===============================================================
 * Approach 1: Brute Force
 * ===============================================================
 *
 * * Traverse every element.
 *
 * Time Complexity:  O(n * m)
 * Space Complexity: O(1)
 */

bool BruteforceSolution(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size();
    int m = matrix[0].size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] == target)
                return true;
        }
    }

    return false;
}

/**
 * ===============================================================
 * Approach 2: Better (Binary Search on Each Row)
 * ===============================================================
 *
 * * For each row:
 *      - If target lies within row range,
 *        apply binary search on that row.
 *
 * Time Complexity:  O(n log m)
 * Space Complexity: O(1)
 */

bool BetterSolution(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size();
    int m = matrix[0].size();

    for (int i = 0; i < n; i++)
    {
        // * Check if target can exist in this row
        if (target >= matrix[i][0] && target <= matrix[i][m - 1])
        {
            // * Apply binary search on row
            int low = 0, high = m - 1;

            while (low <= high)
            {
                int mid = low + (high - low) / 2;

                if (matrix[i][mid] == target)
                    return true;
                else if (matrix[i][mid] < target)
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
    }

    return false;
}

/**
 * ===============================================================
 * Approach 3: Optimal (Treat as 1D Binary Search)
 * ===============================================================
 *
 * * Since matrix behaves like sorted 1D array,
 *   we apply binary search from 0 to (n*m - 1).
 *
 * Mapping index:
 *      row = index / m
 *      col = index % m
 *
 * Time Complexity:  O(log(n*m))
 * Space Complexity: O(1)
 *
 * ! This is the most optimal solution.
 */

bool OptimalSolution(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size();
    int m = matrix[0].size();

    int low = 0;
    int high = n * m - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // * Convert 1D index to 2D position
        int row = mid / m;
        int col = mid % m;

        int value = matrix[row][col];

        if (value == target)
            return true;
        else if (value < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return false;
}

int main()
{
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    int target = 3;

    // bool ans = BruteforceSolution(matrix, target);
    // bool ans = BetterSolution(matrix, target);
    bool ans = OptimalSolution(matrix, target);

    cout << (ans ? "True" : "False");

    return 0;
}