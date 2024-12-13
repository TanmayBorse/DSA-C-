#include <iostream>
#include <vector>

using namespace std;

// Recursive function with memoization to check if there is a subset with the given sum
bool isSubsetSum(vector<int> &nums, int n, int target, vector<vector<int>>& dp) {
    // Base cases
    if (target == 0)
        return true;
    if (n == 0)
        return false;

    // Check if result is already computed
    if (dp[n][target] != -1)
        return dp[n][target];

    // If the current element is greater than the target, skip it
    if (nums[n - 1] > target) {
        dp[n][target] = isSubsetSum(nums, n - 1, target, dp);
    } 
    else {
        // Include the current element or exclude it
        dp[n][target] = isSubsetSum(nums, n - 1, target, dp) ||
                        isSubsetSum(nums, n - 1, target - nums[n - 1], dp);
    }

    return dp[n][target];
}

int main() {
    vector<int> nums = {3, 34, 4, 12, 5, 2};
    int target = 9;

    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));

    if (isSubsetSum(nums,n,target,dp)) {
        cout << "There is a subset with the given target sum." << endl;
    } else {
        cout << "There is no subset with the given target sum." << endl;
    }

    return 0;
}
