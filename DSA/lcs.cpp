#include<iostream>
#include <vector>
#include <math.h>
using namespace std;

int lcs(string& s1, string& s2){

    int n = s1.size();
    int m =  s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, '0'));

    for(int i =1; i <= n; i++){
        for(int j =1; j <= m; j++){

            if(s1[i-1] == s2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }
    return dp[n][m];
}

void printlcs(string &s1, string&s2){

    int n = s1.size();
    int m =  s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, '0'));

    for(int i =1; i <= n; i++){
        for(int j =1; j <= m; j++){

            if(s1[i-1] == s2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }

    int index = dp[n][m];

    string ans(index, '\0');

    int i =n;
    int j =m;
    while(i > 0 && j > 0){

        if(s1[i-1]==s2[j-1]){
            ans[i-1] = s1[i-1];
            i--;
            j--;
            index--;
        }
        else if(dp[i-1][j] > dp[i][j-1]){
            i--;
        }
        else{
            j--;
        }
    }
    cout<<"\n"<<ans;

}

int main(){

    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";

    cout<<"Length of LCS : "<< lcs(s1, s1);
    printlcs(s1, s2);

    return 0;
}