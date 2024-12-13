/* This is a C++ program which uses Recursive function to check if a number 
is prime and sum all prime numbers in a given range of numbers.

a>  Run this program for different input values and validate the logic.
b>  Convert this code to use iterative method and validate the functionalities specified.
*/

#include <iostream>
#include <math.h>
using  namespace std;

/* ******************** Recursive approach ***************************** */

/* 
bool isPrime(int number, int divisor = 2){

    if(number <= 1)
        return false;

    if (number == 2)
        return true;

    if (number % divisor == 0)
        return false;

    if (divisor * divisor > number)
        return true;

    // Recursive case: check if the number is divisible by the next divisor
    return isPrime(number, divisor + 1);

}

int sumOfPrimes(int start, int end){

    if(start < 2) start = 2;

    if (start > end) return 0;

    int sum = isPrime(start) ? start : 0;

    return sum + sumOfPrimes(start + 1, end);

}

*/

/* ******************** iterative approach ***************************** */

bool isPrime(int number){

    if(number <= 1) return false;
    if(number == 2)return true;
    if(number % 2 == 0) return false;

    for(int div = 3; div*div <= number;  div += 2){
        if(number % div ==  0){
            return false;
        }
    }

    return true;
}
int sumOfPrimes(int start, int end){

    if(start < 2) start = 2;
    int sum = 0;

    for(int i =  start; i <= end; i++){
        if(isPrime(i)){
            sum += i;
        }
    }

    return sum;
}
int main(){
    int start, end;
    cout<<"Input the starting number: ";
    cin>> start;
    cout << "Input the ending number: ";
    cin >> end;

// Calculate the sum of prime numbers using recursion

    int sum = sumOfPrimes(start, end);

    cout << "Sum of prime numbers in the said range [" << start << ", " << end << "]: " << sum << endl;

    return 0;

}