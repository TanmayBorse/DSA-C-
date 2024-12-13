/*
uniform distribution of array element, time complexity if array is well unifornly distributed then
loglogn else can ne O(n)
*/

#include <iostream>
using namespace std;

int interpolationSearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {

        if (arr[high] == arr[low]) {
            if (arr[low] == target) return low;
            else return -1;
        }

        int probe = low + (high - low) * (target - arr[low]) / (arr[high] - arr[low]);
        cout << "Probe: " << probe << endl;

        if (arr[probe] == target) return probe;

        if (arr[probe] < target) {
            low = probe + 1;
        }
        else {
            high = probe - 1;
        }
    }

    return -1;
}

int main() {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);

    int index = interpolationSearch(arr, size, 8);

    if (index != -1) {
        cout << "Element found at index: " << index << endl;
    } else {
        cout << "Element not found" << endl;
    }

    return 0;
}
