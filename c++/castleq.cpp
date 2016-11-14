#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <deque>
#include <algorithm>
#include <tuple>
using namespace std;

typedef tuple<int,int,int, char> P;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin >> n;
    char m[n][n];
    for(int i=0; i<n; i++) {
        for(int j=0; j<n;  j++) {
            cin >> m[i][j];
        }
    }
    int x0,y0,x1,y1;
    cin >> x0 >> y0 >> x1 >> y1;
    deque<P> q;
    q.push_back(make_tuple(x0,y0,0,'*'));
    m[x0][y0] = 'X';
    int c=0;
    while (!q.empty()) {
        int x,y,d; char ch;
        tie(x,y,d, ch) = q.front();
        if (x ==x1 && y ==y1) {
            cout << d << endl;
            break;
        }
        m[x][y] = 'X';
        q.pop_front();
        if ((x+1) < n && m[x+1][y] != 'X') 
            q.push_back(make_tuple(x+1, y, 
                                   (ch!='E')? d+1 : d, 'E'));
        if ((y+1) < n && m[x][y+1] != 'X') 
            q.push_back(make_tuple(x, y+1, 
                                   (ch!='N')? d+1 : d, 'N'));
        if ((x-1) >= 0 && m[x-1][y] != 'X') 
            q.push_back(make_tuple(x-1, y, 
                                   (ch!='W')? d+1 : d, 'W'));
        if ((y-1) >= 0 && m[x][y-1] != 'X') 
            q.push_back(make_tuple(x, y-1, 
                                   (ch!='S')? d+1 : d, 'S'));
        
    }
    
    
    return 0;
}

