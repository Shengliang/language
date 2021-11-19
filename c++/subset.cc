// Compiled with: g++ -Wall -std=c++14 -pthread

#include <iostream>
#include <vector>

using namespace std;
/* Given 32-bit mask, compute subsets. */
void backtrack(vector<vector<int>>& ans, int i, vector<int>& cur) {
    if (!cur.empty()) {
      ans.push_back(cur);
    }
    auto &v = ans[0];
    int n = v.size();
    for(; i < n; ++i)  {
      cur.push_back(v[i]); 
      backtrack(ans, i+1, cur);
      cur.pop_back();
    }
}

void buildSet(vector<vector<int>>& ans, uint32_t mask) {
    ans.push_back({});
    auto & v = ans.back();
    while(mask) {
        int cnt = __builtin_ctz(mask);
        v.push_back(cnt);
        mask &= (mask-1);
    }
}

void buildSubset(vector<vector<int>>& ans, uint32_t mask) {
      buildSet(ans, mask);
      vector<int> cur;
      backtrack(ans, 0, cur);
}

void buildSubset2(vector<vector<int>>& ans, uint32_t mask) {
    uint32_t m = mask;
    while (m!=0) {
        buildSet(ans, m);
        m = (m-1)&mask;
    }
}

void print(vector<vector<int>> & ans) {
    for(auto & v : ans) {
        for(auto x: v) {
            cout << x << " " ;
        }
        cout << endl;
    }
}



int main(){
    vector<vector<int>> ans;
    buildSubset2(ans, 0x70);
    print(ans);
    return 0;
}


