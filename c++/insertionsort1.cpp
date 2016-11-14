#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

void pr(vector<int>& ar) {
    for(const auto& e: ar) {
        cout << e << " ";
    }
    cout << endl;
}
void insertionSort(vector <int>  ar) {
    for (int j=1; j< ar.size(); j++) {
        int key = ar[j];
        // insert key into the sorted sequnce ar[0..j-1] 
        int i=j-1;
        while (i>=0 && ar[i] > key) {
            ar[i+1] = ar[i];
            pr(ar);
            i--;
        }
        if ((i+1) != j) {
          ar[i+1] = key;
          pr(ar);
        }
    }
}
int main(void) {
    vector <int>  _ar;
    int _ar_size;
    cin >> _ar_size;
    for(int _ar_i=0; _ar_i<_ar_size; _ar_i++) {
        int _ar_tmp;
        cin >> _ar_tmp;
        _ar.push_back(_ar_tmp); 
    }

    insertionSort(_ar);
    return 0;
}

