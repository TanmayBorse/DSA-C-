// Use the partial code used in Problem No. 1, write a C++ program 
//to find a given number is Armstrong number( For Example, 145 is Armstrong number because :
// 1! + 4! + 5! = 1 + 24 + 120 = 145) 

#include <iostream>
using namespace std;

int fact(int n){
    if(n > 0){
        return n * fact(n-1);
    }
    else return 1;
}

int main(){

    int n = 145;
    int originalnumber = n;
    int sum = 0;
    while(n > 0){
        int rem  = n % 10;
        sum += fact(rem);
        n = n / 10;
    }

    if(sum  ==  originalnumber){
        cout<< originalnumber << " is armstrong number "<< endl; 
    }
    else{
        cout<< originalnumber << " is not armstrong number"<< endl;
    }

    return 0;
}