#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
using namespace std;


// Solution from http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/
uint64_t count( int S[], int m, int n)
{
    // table[i] will be storing the number of solutions for
    // value i. We need n+1 rows as the table is consturcted
    // in bottom up manner using the base case (n = 0)
    vector<uint64_t> table(n+1,0);
 
    // Base case (If given value is 0)
    table[0] = 1;
 
    // Pick all coins one by one and update the table[] values
    // after the index greater than or equal to the value of the
    // picked coin
    for(int i=0; i<m; i++) {
        for(int j=S[i]; j<=n; j++) {
            table[j] += table[j-S[i]];
        }
    }
 
    return table[n];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,m;
    cin >> n >> m;
    int c[m];
    for(int i=0; i<m; i++) {
        cin >> c[i];
    }
    cout << count(c, m, n) << endl;
    return 0;
}

