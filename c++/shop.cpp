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

// Note: This following is based on the editorial solution.

// i-> DistType
// shop i ->  (shop j, distance)
typedef pair<int,int> DistType;

// (dist, shop_i, fish_mask)
typedef tuple<int, int, int> NodeType;

#define MAX_K    10
#define MAX_MASK (1 << MAX_K)
#define MAX_N    1001 // 1 based

int d[MAX_N][MAX_MASK];
 
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,m,k;
    cin >> n >> m >> k;
    // shop -> bit-mask of fishes
    vector<int> shop_fish_mask(n+1);
    // got k fishes so far.
    int fish_mask = 0;
    vector< vector<DistType> > shops(n+1);

    for(int s=1; s<=n; s++) {
        int c,f;
        cin >> c;
        for(int j=0; j<c; j++) {
           cin >> f;
           f -= 1;
           shop_fish_mask[s] |= (1<<f);
        }
    }

    for (int i=0; i<m; i++) {
        int x,y,z;
        cin >> x >> y >> z; 
        shops[x].push_back(DistType(y,z));
        shops[y].push_back(DistType(x,z));
    }
    for (int i = 1; i <= n; i++) {
       for (int j = 0; j < MAX_MASK; j++) {
          d[i][j] = INT_MAX;
       }
    }

    set<NodeType> graph;
    // Start at 1st shop '1'
    d[1][shop_fish_mask[1]] = 0;
    graph.insert(NodeType(0, 1, shop_fish_mask[1]));
    while(!graph.empty()) {
       int curd, i, mask;
       auto& node = *graph.begin();
       tie (curd, i, mask) = node;
       graph.erase(node);
       auto & links = shops[i];
       for(auto & y: links) {
           int to = y.first;
           int cost = y.second;
           int tomask = mask | shop_fish_mask[to];
           if (d[to][tomask] > (curd + cost)) {
               graph.erase(NodeType( d[to][tomask], to, tomask));
               d[to][tomask] = curd + cost;
               graph.insert(NodeType( d[to][tomask], to, tomask));
           }
       }
    }
    int ans = INT_MAX;
    for (int i = 0; i < (1<<k); i++) {
       for (int j = 0; j < (1<<k); j++) {
          if ( (i | j) == ( (1<<k) - 1 ) ) {
              ans = min(ans, max(d[n][i], d[n][j]) );
           }
       }
    }
    cout << ans << endl;
    return 0;
}

