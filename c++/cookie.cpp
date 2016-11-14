#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

void pmap(const map<int, int>& hmap)
{
    for(auto it = begin(hmap); it != end(hmap); it++) {
        cout << it->first << " " << it->second << endl;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,k;
    map<int, int> hmap;
    cin >> n >> k;
    for(int i=0; i<n; i++) {
        int t;
        cin >> t;
        if (hmap.find(t) == end(hmap)) {
            hmap[t] = 1;
        } else {
            hmap[t]+=1;
        }
    }
    int s=0;
    for(;;) {
        auto it = hmap.begin();
        if (it == hmap.end()) {
            s=-1;
            break;
        }
        
        if (it->first >= k)
            break;
        
        auto prev = it;
        it++;
        if (it == hmap.end()) {
            break;
        }

        int x = it->first;
        int y = (x << 1) + prev->first;
        // cout << "RM: " << s << " " << prev->first << " " << it->first << endl;
        hmap.erase(prev);
        hmap.erase(it);
        s++;
        if (hmap.find(y) != end(hmap)) {
            hmap[y] += 1;
        } else {
            hmap[y] = 1;
        }
        // pmap(hmap);
    }
    cout << s << endl;
    return 0;
}

