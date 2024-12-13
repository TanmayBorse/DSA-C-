#include <iostream>
#include <vector>

using namespace std;

void add(int n, vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));
    vector<vector<int>> C11(newSize, vector<int>(newSize));
    vector<vector<int>> C12(newSize, vector<int>(newSize));
    vector<vector<int>> C21(newSize, vector<int>(newSize));
    vector<vector<int>> C22(newSize, vector<int>(newSize));
    vector<vector<int>> M1(newSize, vector<int>(newSize));
    vector<vector<int>> M2(newSize, vector<int>(newSize));
    vector<vector<int>> M3(newSize, vector<int>(newSize));
    vector<vector<int>> M4(newSize, vector<int>(newSize));
    vector<vector<int>> M5(newSize, vector<int>(newSize));
    vector<vector<int>> M6(newSize, vector<int>(newSize));
    vector<vector<int>> M7(newSize, vector<int>(newSize));
    vector<vector<int>> temp1(newSize, vector<int>(newSize));
    vector<vector<int>> temp2(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(newSize, A11, A22, temp1);
    add(newSize, B11, B22, temp2);
    strassen(newSize, temp1, temp2, M1);

    // M2 = (A21 + A22) * B11
    add(newSize, A21, A22, temp1);
    strassen(newSize, temp1, B11, M2);

    // M3 = A11 * (B12 - B22)
    subtract(newSize, B12, B22, temp2);
    strassen(newSize, A11, temp2, M3);

    // M4 = A22 * (B21 - B11)
    subtract(newSize, B21, B11, temp2);
    strassen(newSize, A22, temp2, M4);

    // M5 = (A11 + A12) * B22
    add(newSize, A11, A12, temp1);
    strassen(newSize, temp1, B22, M5);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(newSize, A21, A11, temp1);
    add(newSize, B11, B12, temp2);
    strassen(newSize, temp1, temp2, M6);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(newSize, A12, A22, temp1);
    add(newSize, B21, B22, temp2);
    strassen(newSize, temp1, temp2, M7);

    // Calculate C11, C12, C21, C22
    // C11 = M1 + M4 - M5 + M7
    add(newSize, M1, M4, temp1);
    subtract(newSize, temp1, M5, temp2);
    add(newSize, temp2, M7, C11);

    // C12 = M3 + M5
    add(newSize, M3, M5, C12);

    // C21 = M2 + M4
    add(newSize, M2, M4, C21);

    // C22 = M1 - M2 + M3 + M6
    subtract(newSize, M1, M2, temp1);
    add(newSize, temp1, M3, temp2);
    add(newSize, temp2, M6, C22);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

int main() {
    int n = 4; 
    vector<vector<int>> A = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    vector<vector<int>> B = {{17, 18, 19, 20}, {21, 22, 23, 24}, {25, 26, 27, 28}, {29, 30, 31, 32}};
    vector<vector<int>> C(n, vector<int>(n));

    strassen(n, A, B, C);

    cout << "Product matrix C:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
