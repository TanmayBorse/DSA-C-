/*
Problem statement
There is a frog on the '1st' step of an 'N' stairs long staircase. The frog wants to reach the 'Nth' stair.
'HEIGHT[i]' is the height of the '(i+1)th' stair.If Frog jumps from 'ith' to 'jth' stair, the energy lost in the jump is given by 
absolute value of ( HEIGHT[i-1] - HEIGHT[j-1] ). If the Frog is on 'ith' staircase, he can jump either to '(i+1)th' stair or to '(i+2)th' 
stair. Your task is to find the minimum total energy used by the frog to reach from '1st' stair to 'Nth' stair.

For Example
If the given ‘HEIGHT’ array is [10,20,30,10], the answer 20 as the frog can jump from 1st stair to 2nd stair (|20-10| = 10 energy lost) 
and then a jump from 2nd stair to last stair (|10-20| = 10 energy lost). So, the total energy lost is 20.

Sample Input 1:
2
4
10 20 30 10
3
10 50 10
Sample Output 1:
20
0
Explanation of sample input 1:
For the first test case,
The frog can jump from 1st stair to 2nd stair (|20-10| = 10 energy lost).
Then a jump from the 2nd stair to the last stair (|10-20| = 10 energy lost).
So, the total energy lost is 20 which is the minimum. 
Hence, the answer is 20.

For the second test case:
The frog can jump from 1st stair to 3rd stair (|10-10| = 0 energy lost).
So, the total energy lost is 0 which is the minimum. 
Hence, the answer is 0.
*/

#include <stdlib.h>
#include <vector>
#include <stdio.h>


// RECURSION SOLUTION (Dynamic programming array) (Top down approach)

int rec(int index, vector<int> &heights, vector<int> &dp){

    if(index == 0) return 0;

    if(dp[index] != -1) return dp[index];

    int left = rec(index-1, heights, dp) + abs(heights[index] - heights[index-1]);
    int right = __INT_MAX__;
    if(index > 1){
        right = rec(index-2, heights, dp) + abs(heights[index] - heights[index-2]);
    }

    return dp[index] = min(left, right);
}

// TABULIZATION SOLUTION (Bottom up approach)

int tab(int n, vector<int> &heights){
    vector<int> dp(n , 0);
    dp[0] = 0;

    for (int i = 1; i < n; i++){
        int firstStep = rec(n-1, heights, dp) + abs(heights[i] - heights[i-1]);
        int secondStep = __INT_MAX__;
        if(i > 1){
            secondStep = rec(i-2, heights, dp) + abs(heights[i] - heights[i-2]);
        }
        dp[i] = min(firstStep, secondStep);
    }
    return dp[n-1];
}

// SPACE OPTIMIZATION (instead of dp array we use 3 variables and reuse them)

int spaceOpt(int index, vector<int> &heights){

    int prev = 0;
    int prev2 = 0;
    int curr;

    for (int i = 1; i < n; i++){
        int firstStep = rec(n-1, heights, dp) + abs(heights[i] - heights[i-1]);
        int secondStep = __INT_MAX__;
        if(i > 1){
            secondStep = rec(i-2, heights, dp) + abs(heights[i] - heights[i-2]);
        }

        curr = min(firstStep, secondStep);
        prev2 = prev;
        prev = curr;
    }
    return prev;
}

int main(){

    vector<int> heights = {10,20 ,30,10};
    vector<int> dp(n , -1);
}