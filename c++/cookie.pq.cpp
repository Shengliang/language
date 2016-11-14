#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;


int main() {
    int n,k;
    priority_queue<int,vector<int>,greater<int>>pq;
    cin >> n >> k;
    for(int i=0; i<n; i++) {
        int t;
        cin >> t;
        pq.push(t);
    }
    int s=0;
    int f=0;

    while(!pq.empty()) {
        if (pq.top() >= k) {
            f=1;
            break;
        }
        int x = pq.top(); pq.pop();
        if (pq.empty())
            break;
        int y = pq.top(); pq.pop();
        int z = (y << 1) + x;
        s++;
        // cout << "RM: " << s << " " << x << " " << y << endl;
        pq.push(z);
    }
    if (f==1) {
       cout << s << endl;
    } else {
       cout << -1 << endl;
    }
    return 0;
}

