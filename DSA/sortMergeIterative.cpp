#include <iostream>
#include <algorithm>  // for min function
using namespace std;

void iterativeMergeSort(int arr[], int size) {
   
    for (int currSize = 1; currSize < size; currSize *= 2) {
        
        for (int leftStart = 0; leftStart < size - 1; leftStart += 2 * currSize) {
        
            int mid = min(      leftStart + currSize - 1,       size - 1);
            int rightEnd = min( leftStart + 2 * currSize - 1,   size - 1);

            // Temporary arrays for left and right halves
            int leftSize = mid - leftStart + 1;
            int rightSize = rightEnd - mid;

            int* left = new int[leftSize];
            int* right = new int[rightSize];

            // Copy data to temporary arrays left[] and right[]
            for (int i = 0; i < leftSize; i++) {
                left[i] = arr[leftStart + i];
            }

            for (int i = 0; i < rightSize; i++) {
                right[i] = arr[mid + 1 + i];
            }

            // Merge the temporary arrays back into arr[]
            int i = 0, j = 0, k = leftStart;

            while (i < leftSize && j < rightSize) {
                if (left[i] <= right[j]) {
                    arr[k++] = left[i++];
                }
                else {
                    arr[k++] = right[j++];
                }
            }

            while (i < leftSize) {
                arr[k++] = left[i++];
            }

            while (j < rightSize) {
                arr[k++] = right[j++];
            }

            // Deallocate the temporary arrays
            delete[] left;
            delete[] right;
        }
    }
}

// Driver code to test the Iterative Merge Sort function
int main() {
    int arr[] = { 38, 27, 43, 3, 9, 82, 10 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    iterativeMergeSort(arr, size);

    cout << "Sorted array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
