#include <iostream>
#include <stack>
#include <string>
using namespace std;

int precce(char c){
    if(c == '+' || c == '-'){
        return 1;
    }

    if(c == '*' || c == '/'){
        return 2;
    }

    return 0;
}

bool isoperand(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

bool isoperator(char c){
    return(c == '+' || c == '-' || c == '*' || c == '/');
}

string function(string s){

    stack<char> st;
    string post;

    for(char c : s){

        if(isoperand(c)){
            post += c;
        }

        else if(c == '('){
            st.push(c);
        }

        else if(c == ')'){

            while(!st.empty() && st.top() != '('){
                post += st.top();
                st.pop();
            }
            st.pop(); // pop (
        }

        else if(isoperator(c)){

            while(!st.empty() && precce(st.top()) >= precce(c)){
                post += st.top();
                st.pop();
            }

            st.push(c);
        }
    }

    while(!st.empty()){
        post += st.top();
        st.pop();
    }

    return post;
}


int main(){

    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;

    string postfix = function(infix);

    cout << "Postfix expression: " << postfix << endl;

    return 0;
}