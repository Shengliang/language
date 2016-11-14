#include <time.h>
#include <stdlib.h>

#include <cmath>
#include <cstdio>
#include <climits>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <cstdint>

using namespace std;

/*
 * K-means clustering algorithm
 * https://www.youtube.com/watch?v=_aWzGGNrcic
 *
 * for each point xj
       - find nearest centroid cj
       - assign the point xi to cluster j
 * for each cluster j = 1..k
      - new centeroid cj = mean of all points xj
 */

int *X;
int *W;

uint64_t dist(int*x, int *w, int i, int j) {
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
    map<int, int> vi;
    for(int i=0; i<n; i++) {
        cin >> x[i] >> w[i];
        vi[x[i]] = i;
    }
    int c[k], nc[k];
    map<int,bool> h;
    srand(time(NULL));
    int j=0;
    if (k==1) {
        int t=rand()%n;
        c[j] = t;
    } else if (k>=2) {
        c[0] = 0;
        c[k-1] = n-1;
        j=1;
        while(j<(k-1)) {
            int t = rand() % n;
            if (h.find(t) != end(h)) {
                continue;
            }
            h[t] = true;
            c[j] = t;    
            //cout << "Random pick:" << x[t] << " " << w[t] << endl;
            j++;
        }
    }
   int done = 0;
    map<int, bool>  dmap;
 
    
while(done < k) {
   
    vector<int> xc[k];
    uint64_t ans[k], tans = 0;
    for(int j=0;j<k;j++) ans[j] = 0;
    
    for(int i=0; i<n;i++) {
        uint64_t d = 0;
        for(int j=0; j<k; j++) {            
            uint64_t t = dist(x,w, i, c[j]); 
            //cout << "c[j]:" << c[j] << " " << t << endl;
            if (j==0) {
                d=t;
                cc[i]=j;
            }
            else if (t < d) {
                d=t;
                cc[i] = j;
            }
        }
        ans[cc[i]]+=d;
        tans+=d;
        xc[cc[i]].push_back(i);
       //cout << x[i] << " is--> " << x[c[cc[i]]] << " d:" <<  d << " ans:" << ans[cc[i]] <<  endl;
    }
   
    for(int j=0; j<k; j++){
          //cout << "ans:j:" << j << " " << ans[j]  << endl;
          uint64_t s=0,tw=0;
          for(auto& xci : xc[j]) {
              //cout << xci << " " << x[xci] << endl;
              s += x[xci]*w[xci];
              tw += w[xci];
          }
          s /= tw;
         // cout << "new center:" << s << endl;
          int prev=-1;
          for(int i=0; i< xc[j].size(); i++) {
              int t = xc[j][i];
              if (s == x[t]) {
                  nc[j] = t;
                  break;
              } else if (s > x[t]) {
                  prev=t;
              } else if  (s < x[t]) {
                  if(prev!=-1) {
                      if ( abs(s-x[prev]) < abs(s-x[t])) {
                          nc[j] = prev;
                      }  else {
                          nc[j]  = t;
                      }
                  } else {
                      nc[j] = t;
                  }
                      break;
              }
              
              
          }
 
         // cout << "new c:" << j << " " << s <<  " " << x[nc[j]] << endl;

          if (c[j] == nc[j]) {
              if (dmap.find(j) == end(dmap)) {
                  dmap[j] = true;
                  done++;
              }
              if(done==k) {
                  cout << tans << endl;
                  break;
              }
          } else {
              c[j] = nc[j];
          }    
    }       

    
}
    
    
    return 0;
}
