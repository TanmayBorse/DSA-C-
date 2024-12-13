/*
Binary knpasack is also 0/1 knapsack problem
solve using dynamic programming memoization and in commensts tabulation approach
either take item or not take item base on maximum weigth W allowed
*/

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int binaryKnapsack(int ind, int W, vector<int> &val, vector<int> &wt, vector<vector<int>> &dp){

    if(ind == 0){
        if(wt[0] <= W) return val[0];
        return 0;
    }

    if(dp[ind][W] != -1) return dp[ind][W];

    int notTake = 0 + binaryKnapsack(ind-1, W, val, wt, dp);
    int take = INT8_MIN;
    if(wt[ind] <= W){
        take = val[ind] + binaryKnapsack(ind-1, W - wt[ind], val, wt, dp);
    }

    return dp[ind][W] = max(take , notTake);
}

int main(){
    vector<int> val = {30, 40, 60};
    vector<int> wt = { 2, 5, 8};
    int W = 8;

    int n = val.size();

    vector<vector<int>> dp (n, vector<int>(W+1, -1));

    cout<< binaryKnapsack(n-1, W, val, wt, dp)<<endl;

    /*
    vector<vector<int>> tab(n, vector<int>(W+1, 0));
    for(int i = wt[0]; i <= W; i++){
        tab[0][i] = val[0];
    }

    for(int ind = 1; ind < n; ind++){
        for(int w = 0; w <= W; w++){
            
            int notTake = 0 + tab[ind-1][w];
            int take = 0;
            if(wt[ind] <= W){
                take = val[ind] + tab[ind-1][w - wt[ind]];
            }
            tab[ind][W] = max(take , notTake);
        }
    }

    cout<<tab[n-1][W];
    */
    
    return 0;
}