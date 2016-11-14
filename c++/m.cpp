#include <time.h>
#include <stdlib.h>

#include <cmath>
#include <cstdio>
#include <climits>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;


int *X;
int *W;

int dist(int*x, int *w, int i, int j) {
    return abs(x[i]-x[j])*w[i];
}

bool mycmp(int i, int j) {
    return X[i]*W[i] < X[j]*W[j];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,k;
    cin >> n >> k;
    int x[n], w[n], cc[n];
    X=x;W=w;
    for(int i=0; i<n; i++) {
        cin >> x[i] >> w[i];
    }
    int c[k], nc[k];
    map<int,bool> h;
    srand(time(NULL));
    int j=0;
    while(j<k) {
        int t = rand() % n;
        if (h.find(t) != end(h)) {
            continue;
        }
        h[t] = true;
        c[j] = t;    
       // cout << "Random pick:" << x[t] << " " << w[t] << endl;
        j++;
    }
    
   int done = 0;
    map<int, bool>  dmap;
while(done < k) {
   
    vector<int> lc[k];
    vector<int> rc[k];
    int ans =0;
    for(int i=0; i<n;i++) {
        int d=INT_MAX;
        for(int j=0; j<k; j++) {
            int t = dist(x,w, i, c[j]);
            if (t < d) {
                d=t;
                cc[i] = j;
            }
        }
        ans+=d;
        if ( i < c[j]) 
           lc[cc[i]].push_back(i);
        else
           rc[cc[i]].push_back(i);
       // cout << x[i] << " is--> " << cc[i] << endl;
    }
    
    for(int j=0; j<k; j++){
          int md= INT_MAX;
          int s=0;
         
          for(auto& lci : lc[j]) {                
          }
        
          for(auto& rci : rc[j]) {                
          }
         
          if (c[j] == nc[j]) {
              if (dmap.find(j) == end(dmap)) {
                  dmap[j] = true;
                  done++;
              }
              if(done==k) 
                  cout << ans << endl;
          } else {
              c[j] = nc[j];
          }    
    }       

    
}
    
    
    return 0;
}

