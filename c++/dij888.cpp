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
int   adj[MAX_N][MAX_N];
int   d[MAX_N];
int   f[MAX_N];

typedef pair<int,int> Node;
struct classcomp {
    bool operator()(const int &a, const int &b) const {
        return ((d[a] == d[b]) && (a < b)) || (d[a] < d[b]);
    }
};

void foo(void)
{
    int n,m;
    cin >> n >> m;
    set<int, classcomp> Q;
    vector<int> lnk[MAX_N];
    for(int i=1; i<=n; i++) {
       d[i] = INT_MAX;   // Unknown distance from source to v
       f[i] = 0;
        for(int j=1; j<=n; j++) {
            adj[i][j] = INT_MAX;
        }
    }

    for(int e=0; e<m; e++) {
        int u,v,d;
        cin >> u >> v >> d;
        if ( (u!=v) && (adj[u][v] > d)) {
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
    // Distance from source to source is ZERO.
    d[s] = 0;
    Q.insert(s);
    f[s] = 1;
    while(!Q.empty()) {   
        register int u = *Q.begin();
        Q.erase(u);
        f[u] = 2;
        //cout << u << ":" << d[u] << endl;    
        // for each neighbor v of u, where v is still in Q
        for(int v : lnk[u]) 
        {
           if (v==s)
               continue;
           if (f[v]==2) {
               continue;
           }
           //cout << u << "=>" << v << " " << node.first << endl;
           register int alt = d[u] + adj[u][v];
           if (alt < d[v]) { //  A shorter path to v has been found
               if (f[v] == 1) {
		  //cout << "Erase:" << v << endl;
                  Q.erase(v);
               }
               //cout << u << "=>" << v << " " << node.first << " " << d[v] << ":=" << alt << endl;
               d[v] = alt;
               Q.insert(v);
               f[v]=1;
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



