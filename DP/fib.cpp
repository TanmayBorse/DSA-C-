#include <vector>
#include<iostream>
using namespace std;

// recusrion method

/*int fib(int n, vector<int> &dp){
    if(n <= 1){
        return n;
    }

    if(dp[n] != -1) return dp[n];

    return dp[n] = fib(n-1, dp) + fib(n-2, dp);
}

int main(){
    int n = 5;
    cout<<"Enter number to find series";
    cin>>n;
    vector<int> dp(n, -1);
    cout<<fib(n, dp);
    return 0;
}*/


// by tabular method
int main(){
    int n = 6;

    vector<int> dp(n);
    dp[0] = 0;
    dp[1] = 1;

    for(int i = 2; i <= n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }

    cout<<dp[n];
    return 0;
}