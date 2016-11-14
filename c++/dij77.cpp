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

//typedef pair<int,int> Node;
class Node {
public:
    int n;
    Node(int x) : n(x) { }
    bool operator<(const Node & o) const {
       return ((d[n] == d[o.n]) && (n < o.n)) || (d[n] < d[o.n]); 
    }
};
/*
struct classcomp {
    bool operator()(const Node &a, const Node &b) const {
        return ((d[a.n] == d[b.n]) && (a.n < b.n)) || (d[a.n] < d[b.n]);
    }
};
*/



void foo(void)
{
    int n,m;
    cin >> n >> m;
    //set<Node, classcomp> Q;
    set<Node> Q;
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
    Q.insert(Node(s));
    f[s] = 1;
    while(!Q.empty()) {   
        auto it = Q.begin();
        register int u = it->n;
        Q.erase(it);
        f[u] = 2;
        //cout << u << ":" << d[u] << endl;    
        // for each neighbor v of u, where v is still in Q
        int dxmin = INT_MAX;
        int nv = -1;
        for(int v : lnk[u]) 
        {
           if (v==s)
               continue;
           if (f[v]==2) {
               continue;
           }
           //cout << u << "=>" << v << " " << adj[u][v] << endl;
           register int alt = d[u] + adj[u][v];
           if (alt < d[v]) { //  A shorter path to v has been found
              // cout << u << "=>" << v << " " << adj[u][v] << " " << d[v] << ":=" << alt << endl;
               d[v] = alt;
               if (dxmin > alt) {
                  nv = v;
                  dxmin = alt;
               } 
           }
       }
       if (nv != -1) {
          if (f[nv] == 1) {
             Q.erase(Q.find(Node(nv)));
          }
          Q.insert(Node(nv));
          f[nv]=1;
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




