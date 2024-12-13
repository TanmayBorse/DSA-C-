/*
You are given an array of positive intregers and you have to tell how many
different ways to selecting the element from array are there such that 
the sum of choosen elements is equal to thr target number k
*/

#include <iostream>
#include <vector>
using namespace std;

int f(int ind, int k, vector<int> &nums, vector<vector<int>> &dp){
        if(k == 0) return 1;
        if(ind == 0) return nums[0] == k;

        if(dp[ind][k] != -1) return dp[ind][k];
        
        int notTake = f(ind-1, k, nums, dp);
        int take = 0;
        if(nums[ind] <= k){
            take = f(ind - 1, k - nums[ind], nums, dp);
        }

        return dp[ind][k] = take + notTake;
    }

int main(){

    vector<int> nums = {1,2,2,3};
    int k = 3; // target element
    int n = nums.size();

    vector<vector<int>> dp(n , vector<int>(k+1, -1));

    cout<<f(n-1, k, nums, dp);
    return 0;
}
