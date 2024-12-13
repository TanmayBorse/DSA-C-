#include <iostream>
#include <vector>
#define N 4

using namespace std;

vector<vector<int>> solutions;
int solutionCount = 0;
/*
void printSolution(const vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? 'Q' : '.') << " ";
        }
        cout << endl;
    }
    cout << endl;
}*/

bool isSafe(const vector<vector<int>> &board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i][col]) {
            return false;
        }
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

void storeSolution(const vector<vector<int>> &board) {
    vector<int> solution(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j]) {
                solution[i] = j + 1;
            }
        }
    }
    solutions.push_back(solution);
    solutionCount++;
}

void solveNQueens(vector<vector<int>> &board, int row) {
    if (row == N) {
        storeSolution(board);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;
            solveNQueens(board, row + 1);
            board[row][col] = 0; // Backtrack
        }
    }
}

int main() {
    
    vector<vector<int>> board(N, vector<int>(N, 0));
    solveNQueens(board, 0);

    cout << "Total number of solutions: " << solutionCount << endl;
    cout << "Solutions:" << endl;

    for (int i = 0; i < solutionCount; i++) {
        cout << "Solution " << i + 1 << ": ";
        for (int j = 0; j < N; j++) {
            cout << solutions[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
