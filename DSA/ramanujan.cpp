//In Mathematic, 2520 can be divided by all the numbers from 1 to 10. Write a C++ program to validate this statement.

#include <iostream>
using namespace std;

int main(){

    int n = 2520;

    bool valid =  true;

    for(int i = 1; i <= 10; i++){
        if(n % i != 0){
            valid = false;
            break;
        }
    }

    if(valid){
        cout << n << " is divisible by all number in 1 to 10"<< endl;
    }
    else{
        cout<< n<< " is not divisible by all number in 1 to 10"<< endl;
    }

    return 0;
}