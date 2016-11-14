#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

void pq(const list<int>& q) {
    for(const auto & e : q) {
        cout << e << ' ';
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int m,n;
    cin >> m >> n;
    list<int> q;
    for(int i=0; i< m; i++) {
        int t;
        cin >> t; 
        q.push_back(t);
    }
    for (int i=0; i<n; i++) {
        int op, s, e;
        cin >> op >> s >> e;
        auto its = q.begin();
        auto ite = q.begin();
        advance(its, s-1);
        advance(ite, e);
        if (op == 1) {
            q.splice(q.begin(), q, its, ite);     
        }
        else if (op == 2) {
            q.splice(q.end(), q, its, ite); 
        }
        // cout << op << " " << s << " " << e << endl;
        // pq(q);
    }
    cout << q.front() - q.back() << endl;
    pq(q);
    return 0;
}

