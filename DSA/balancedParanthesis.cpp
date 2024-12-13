#include <iostream>
#include <stack>
using namespace std;

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') || 
           (open == '{' && close == '}') || 
           (open == '[' && close == ']');
}

bool isvalid(string s){
    
    stack<char> st;

    for(int i = 0; i < s.length(); i++){
        char ch = s[i];

        if(ch == '(' || ch == '[' || ch == '{'){
            st.push(ch);
        }

        else if(ch ==')' || ch == ']' || ch == '}'){
            if(st.empty() || !isMatchingPair(st.top(), ch)){
                return false;
            }
            st.pop();
        }
    }

    return st.empty();
}

int main(){

    string s = "({[()]})";

    if(isvalid(s)){
        cout<<"Balanced";
    }
    else{
        cout<<"unbalanced";
    }

    return 0;
}