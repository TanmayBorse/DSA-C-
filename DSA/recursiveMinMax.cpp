/*This is a C++ program which uses Recursive function to find the max and min elements in an array.

a>  Run this program for different input values and validate the logic.
b>  Modify the code to accept any number of inputs and find the maximum and minimum.
c>  Write a logic to display the times of execution findMax, findMin for a given number of input.
d>  Convert this code to use iterative method and validate the functionalities specified in a,b,c.
*/
 

#include <iostream>
using namespace std;

int findMax(int nums[], int start, int end, int &maxcount){

    maxcount++;

    // Base case: when there is only one element, it is the maximum
    if (start == end) return nums[start];

    /* Recursive case: divide the array in half and find the maximum in each half, then return the maximum of the two halves */
  
    int mid = (start + end) / 2;

    int max1 = findMax(nums, start, mid, maxcount);
    int max2 = findMax(nums, mid + 1, end, maxcount);
    
    return (max1 > max2) ? max1 : max2;
}

// Recursive function to find the minimum element in an array

int findMin(int nums[], int start, int end, int &mincount){
    
    mincount++;
    
    // Base case: when there is only one element, it is the minimum

    if (start == end) return nums[start];

    /* Recursive case: Divide the array in half and find the minimum in each half,then return the minimum of the two halves */

    int mid  =  start + (end - start) / 2 ;

    int min1 = findMin(nums, start, mid, mincount);
    int min2 = findMin(nums, mid + 1, end, mincount);

    return (min1 < min2) ? min1 : min2;
}

int main(){
    int n;
    cout<<"Enter number of elements you want to enter in array :";
    cin>>n;

    int nums[n];
    int num;
    
    cout<<"Enter elements in array :"<<endl;
    for(int i = 0; i < n; i++){
        cin>>num;
        nums[i] = num;
    }

    // int nums[] = { 9, 2, 4, 0, 2, 2, 3, 4, 5, 7 };
    // int size = sizeof(nums) / sizeof(nums[0]);
    
    cout << "\nArray elements: " << endl;
    
    for (size_t i = 0; i < n; i++){
        cout << nums[i] << ' ';    
    }

    // Find the max and min elements in the array using recursion

    int mincount = 0;
    int maxcount = 0;
    
    int max = findMax(nums, 0, n - 1, maxcount);
    int min = findMin(nums, 0, n - 1, mincount);
    
    cout << "\nMaximum element: " << max <<" count is "<<maxcount<< endl;
    cout << "Minimum element: " << min <<" count is "<< mincount<< endl;
    
    return 0;
}