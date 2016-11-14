#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <climits>
using namespace std;

#define MAX_N    3001
int adj[MAX_N][MAX_N];
int   d[MAX_N];
int   f[MAX_N];

typedef pair<int,int> Edge;
void foo(void)
{
    int n,m;
    cin >> n >> m;
    unordered_set<int> Q;
    vector<int> lnk[MAX_N];
    for(int i=1; i<=n; i++) {
       d[i] = INT_MAX;
       f[i] = 0;
       for(int j=1; j<=n; j++) {
           adj[i][j] = INT_MAX;
       }
    }

    for(int e=0; e<m; e++) {
        int u,v,d;
        cin >> u >> v >> d;
        if ((adj[u][v] > d) && (u!=v)) {
             if (adj[u][v] == INT_MAX) {
               lnk[u].push_back(v);
               lnk[v].push_back(u);   
            }
            adj[u][v] = d;
            adj[v][u] = d;
        }
    }

    int s;
    cin >> s;

    d[s] = 0;
    Q.insert(s);
    while(!Q.empty()) {
      
        int minu = INT_MAX;
        int u = -1;
        for (auto it=Q.begin(); it!=Q.end(); ++it)
        {
            int i = *it;
            if (d[i] < minu)  {   
                u = i;
                minu = d[i];
            }
        }
        if (u != -1) {
            Q.erase(u);
        } else {
            break;
        }
        
        for(int v : lnk[u])
        {
           if (v==s)
             continue; 
           if (f[v] == 2) 
             continue;
           int alt = d[u] + adj[u][v];
           if (d[v] > alt) {
               if (f[v] == 1) {
                 Q.erase(v);
               }
               d[v] = alt;
               Q.insert(v);
               f[v] = 1;
           }
       }
    }
    
    for (int j=1; j <= n; j++) {
      if (s != j) {
          if (d[j]==INT_MAX) {
              cout << -1 << " ";
          } else {
              cout << d[j] << " ";
          }    
      }        
    }
    cout << endl;
}
 
int main() {
    int T;
    cin >> T;
    for(int i=0; i<T; i++) {
      foo();
    }
    return 0;
}


