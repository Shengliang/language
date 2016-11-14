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
    bool operator()(const Node &a, const Node &b) const {
        return ((a.first == b.first) && (a.second < b.second)) || (a.first < b.first);
    }
};

void foo(void)
{
    int n,m;
    cin >> n >> m;
    set<Node, classcomp> Q;
    set<Node, classcomp> lnk[MAX_N];
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
            if (adj[u][v] != INT_MAX) {
             lnk[u].erase(Node(adj[u][v],v));
             lnk[v].erase(Node(adj[u][v],u));                
            }
            lnk[u].insert(Node(d,v));
            lnk[v].insert(Node(d,u)); 
            adj[u][v] = d;
            adj[v][u] = d;
        }
    }

    int s;
    cin >> s;
    // Distance from source to source is ZERO.
    d[s] = 0;
    Q.insert(Node(0,s));
    f[s] = 1;
    while(!Q.empty()) {   
        auto it = Q.begin();
        register int u = it->second;
        Q.erase(it);
        f[u] = 2;
        //cout << u << ":" << d[u] << endl;    
        // for each neighbor v of u, where v is still in Q
        for(const auto& node : lnk[u]) 
        {
           int v= node.second;
           if (v==s)
               continue;
           if (f[v]==2) {
               continue;
           }
           //cout << u << "=>" << v << " " << node.first << endl;
           register int alt = d[u] + node.first;
           if (alt < d[v]) { //  A shorter path to v has been found
               if (f[v] == 1) {
		  //cout << "Erase:" << v << endl;
                  Q.erase(Q.find(Node(d[v], v)));
               }
               //cout << u << "=>" << v << " " << node.first << " " << d[v] << ":=" << alt << endl;
               d[v] = alt;
               Q.insert(Node(d[v],v));
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



