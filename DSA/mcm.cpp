#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Memoization table
vector<vector<int>> dp;
vector<vector<int>> split;

int matrixChainMultiplication(const vector<int> &arr, int i, int j) {
    
    if (i == j) return 0;

    // If the result is already computed, return it
    if (dp[i][j] != -1) return dp[i][j];

    int minCost = INT_MAX;

    // Try every possible split point
    for (int k = i; k < j; k++) {
        int cost = matrixChainMultiplication(arr, i, k) +
                   matrixChainMultiplication(arr, k + 1, j) +
                   arr[i - 1] * arr[k] * arr[j];

        if (cost < minCost) {
            minCost = cost;
            split[i][j] = k;
        }
    }

    // Store the result in the dp table
    return dp[i][j] = minCost;
}

// Function to print the optimal parenthesization
void printOptimalParenthesization(int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printOptimalParenthesization(i, split[i][j]);
        printOptimalParenthesization(split[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
    vector<int> arr = {5, 4, 6, 2, 7}; // Dimensions of matrices

    int n = arr.size();
    dp.assign(n, vector<int>(n, -1)); // Initialize memoization table with -1
    split.assign(n, vector<int>(n, 0)); // Table to store the split points

    int minCost = matrixChainMultiplication(arr, 1, n - 1);
    cout << "Minimum number of scalar multiplications: " << minCost << endl;

    cout << "Optimal parenthesization: ";
    printOptimalParenthesization(1, n - 1);
    cout << endl;

    return 0;
}

/*
You are given four matrices with dimensions: 5x4, 4x6, 6x2, and 2x7.
Determine the minimum number of scalar multiplications 
required to compute the product of these matrices. Also, provide 
the optimal parenthesization of the matrices.
*/