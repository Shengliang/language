#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <climits>
using namespace std;

#define MAX_N    3001
int adj[MAX_N][MAX_N];
int   d[MAX_N][MAX_N];

typedef pair<int,int> Node;
void foo(void)
{
    int n,m;
    cin >> n >> m;
    for(int i=1; i<(n+1); i++) {
       for(int j=1; j<(n+1); j++) {
           adj[i][j] = INT_MAX;
           d[i][j] = INT_MAX;
       }
    }

    for(int e=0; e<m; e++) {
        int u,v,d;
        cin >> u >> v >> d;
        adj[u][v] = min(adj[u][v],d);  
        adj[v][u] = min(adj[v][u],d);  
    }

    int s;
    cin >> s;

    set<Node> graph;
    d[1][1] = 0;
    graph.insert(Node(1, 0));
    while(!graph.empty()) {
       auto & node = *graph.begin();
       int i = node.first;
       int x = node.second;
       graph.erase(node);
       for(int j=1; j<(n+1); j++) {
           if (j==s)
             continue; 
           if (j==i)
             continue; 
           if (adj[i][j]==INT_MAX)
             continue; 
           int nd = x + adj[i][j];
           if (d[i][j] > nd) {
               // cout << i << "->" << j << ":" << d[i][j] << " " << nd << endl;
               graph.erase(Node(j, d[i][j]));
               d[i][j] = nd;
               d[s][j] = min(d[s][j], nd);
               graph.insert(Node(j, d[i][j]));
           }
       }
    }
    for (int j=1; j <= n; j++) {
      if (s != j)
         cout << d[s][j] << " ";
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

