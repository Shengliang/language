#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>
#include <climits>
using namespace std;

typedef tuple<int,int,int, char> P;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin >> n;
    char m[n][n];
    bool v[n][n];
    int  D[n][n];
    for(int i=0; i<n; i++) {
        for(int j=0; j<n;  j++) {
            cin >> m[i][j];
            v[i][j]=false;
            D[i][j]=INT_MAX;
        }
    }
    int x0,y0,x1,y1;
    cin >> x0 >> y0 >> x1 >> y1;

    auto cmp = [](P left, P right) {
        return get<2>(left) > get<2>(right);
    };
    priority_queue<P,vector<P>, decltype(cmp)> q(cmp);    
    v[x0][y0] = true;
    D[x0][y0] = 0;
    q.push(make_tuple(x0,y0,0,'*'));
    int c=0;
    int f=0;
    while (!q.empty()) {
        int x,y,d; char ch;
        tie(x,y,d, ch) = q.top();
        if (x ==x1 && y ==y1) {
            cout << d << endl;
            f=1;
            break;
        }
        q.pop();
        for (int xi=x+1; (xi < n && m[xi][y] != 'X'); xi++) {
           if (!v[xi][y]) {
              v[xi][y] = true;
              D[xi][y] = d+1;
              q.push(make_tuple(xi, y, d+1, 'E'));
           }
        }
        for (int yi=y+1; (yi < n && m[x][yi] != 'X'); yi++) { 
           if (!v[x][yi]) {
             v[x][yi] = true;
             D[x][yi] = d+1;
             q.push(make_tuple(x, yi, d+1, 'N'));
           }
        }
        for (int xi=x-1; (xi >= 0 && m[xi][y] != 'X'); xi--) {
           if (!v[xi][y]) {
             v[xi][y] = true;
             D[xi][y] = d+1;
             q.push(make_tuple(xi, y, d+1, 'W'));
           }
        }
        for (int yi=y-1; (yi >= 0 && m[x][yi] != 'X'); yi--) { 
           if (!v[x][yi]) {
             v[x][yi] = true;
             D[x][yi] = d+1;
             q.push(make_tuple(x, yi, d+1, 'S'));
           }
        }

#if 0
    for(int i=0; i<n; i++) {
        for(int j=0; j<n;  j++) {
            int d = D[i][j];
            if (d==INT_MAX) { cout << "? "; }
            else cout << D[i][j] <<  " ";
        }
        cout << endl;
    }
    cout << endl;
#endif
        
    }
    if (f==0) {
       cout << -1 << endl;
    } 
    
    return 0;
}

