#include <iostream> 
using namespace std;

// Function to swap two elements
void swap(int arr[] , int pos1, int pos2){ 
    int temp = arr[pos1]; 
    arr[pos1] = arr[pos2]; 
    arr[pos2] = temp; 
} 

// Partition function with right pivot
/*
int partition(int arr[], int low, int high){ 
    
    int pivot = arr[low];
    int i = low; 
    int j = high; 

    while(i < j ){

        while( arr[i] <= pivot && i <= high){
            i++;
        }

        while(arr[j] > pivot && j >= low){
            j--;
        }

        if( i < j) swap(arr, i, j);
    } 
    swap(arr, low, j);
    return j;
} */

int partition(int arr[], int low, int high){ 
    
    int pivot = arr[high];
    int i = low; 
    int j = low; 

    while ( i <= high){

        if(arr[i] > pivot){
            i++;
        }
        else{
            swap(arr, i ,j);
            i++;
            j++;
        }
    }
    return j-1;
}

// QuickSort function
void quickSort(int arr[], int low, int high){ 
    if(low < high){ 
        int pos = partition(arr, low, high); 
        quickSort(arr, low, pos-1); 
        quickSort(arr, pos+1, high); 
    } 
} 

int main() 
{   
    /*
    int n; 
    cout << "Enter the size of array: "; 
    cin >> n; 

    int arr[n]; // Can also use dynamic allocation or vector
    cout << "Enter the elements of the array: "; 
    for(int i = 0; i < n; i++){ 
        cin >> arr[i]; 
    } 
    */
    int arr[] = { 8, 2, 5, 1, 7, 6, 3, 15, 11, 13, 12, 0};
    int n = 12;
    quickSort(arr, 0, n-1); 

    cout << "The sorted array is: "; 
    for(int i = 0; i < n; i++){ 
        cout << arr[i] << " "; 
    } 
    cout << endl;

    return 0; 
}
