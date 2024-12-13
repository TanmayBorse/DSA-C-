/*
Best case: O(1) when the target is the first element.
Average case: O(log n), similar to binary search.
Worst case: O(log n).
*/

#include <iostream>
using namespace std;

int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Exponential search function
int exponentialSearch(int arr[], int size, int target) {
    
    if (arr[0] == target)
        return 0;

    // Find the range where the target might be
    int i = 1;
    while (i < size && arr[i] <= target) {
        i *= 2;
    }

    return binarySearch(arr, i / 2, min(i, size - 1), target);
}

int main() {
    
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int size = sizeof(arr) / sizeof(arr[0]);

    int target = 8;
    int index = exponentialSearch(arr, size, target);

    if (index != -1) {
        cout << "Element found at index: " << index << endl;
    } else {
        cout << "Element not found" << endl;
    }

    return 0;
}