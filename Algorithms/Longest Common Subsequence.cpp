// Longest Common Subsequence
// Dynamic Programing 
// cost = O(2^n)
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int max(int a , int b) { return (a>b)?a:b ; }

int lcs(char X[], char Y[], int m, int n){
    if(m == 0 || n == 0)
        return 0;
    else if(X[m-1] == Y[n-1])
        return 1+lcs(X, Y, m-1, n-1);
    else   
        return max(lcs(X, Y, m, n-1) ,lcs(X, Y, m-1, n));
}

int main(){
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";

    int m = strlen(X);
    int n = strlen(Y);

    cout << "Length of LCS is : " << lcs(X, Y, m, n);
    return 0;
}