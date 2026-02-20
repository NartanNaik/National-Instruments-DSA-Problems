#include <bits/stdc++.h>
using namespace std;

int BruteforceSolution(vector<int> &a)
{
    int mini = a[0];
    for (int i = 0; i < a.size(); i++)
    {
        mini = min(mini, a[i]);
    }

    return mini;
}

int OptimalSolution(vector<int> &a)
{
    int low = 0, high = a.size() - 1;

    while (low < high)
    {
        if (a[low] <= a[high])
        {
            return a[low];
        }

        int mid = low + (high - low) / 2;
        
        if (a[mid] > a[high])
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    return a[low];
}

int main()
{
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    // int ans = BruteforceSolution(nums);
    int ans = OptimalSolution(nums);
    cout << ans;
    return 0;
}