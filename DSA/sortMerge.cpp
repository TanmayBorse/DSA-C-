#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int* leftArr = new int[leftSize];
    int* rightArr = new int[rightSize];

    for (int i = 0; i < leftSize; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0;  // Initial index of left subarray
    int j = 0;  // Initial index of right subarray
    int k = left;  // Initial index of merged subarray

    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < leftSize) {
        arr[k++] = leftArr[i++];
    }

    while (j < rightSize) {
        arr[k++] = rightArr[j++];
    }

}

void recursiveMergeSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    recursiveMergeSort(arr, left, mid);
    recursiveMergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

int main() {
    int arr[] = { 38, 27, 43, 3, 9, 82, 10 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    recursiveMergeSort(arr, 0, size - 1);

    cout << "Sorted array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
