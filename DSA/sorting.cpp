#include <iostream>
using namespace std;

void swap(int &a, int &b){

    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int arr[], int size){

    bool swapped;

    for(int i = 0; i < size; i++){

        swapped = false;

        for(int j = 1; j < size - i; j++){

            if(arr[j] < arr[j-1]){
                swap(arr[j], arr[j-1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

void selectionSort(int arr[], int n){
    
    for(int i = 0 ; i <= n-2; i++){
        int mini = i;

        for(int j = i; j <= n-1; j++){
            if(arr[j] < arr[mini]){
                mini = j;
            }
        }
        swap(arr[i], arr[mini]);
    }
}

void insertionSort(int arr[], int n){

    for(int i = 0; i < n ; i++){
        
        int j = i;

        while( j > 0 && arr[j-1] > arr[j]){
            swap(arr[j-1], arr[j]);
            j--;
        }
        
    }
}

void print(int arr[], int n){

    for (int i = 0; i < n; i++)
    {
        cout<<arr[i]<<" ";
    }
    
}

int main(){
    int arr[] = { 5, 4, 9, 1, 2, 7, 3};

    int size = sizeof(arr) / sizeof(arr[0]);

    //bubbleSort(arr, size);

    //selectionSort(arr, size);

    insertionSort(arr, size);

    print(arr, size);

    return 0;

}