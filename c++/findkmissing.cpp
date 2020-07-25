#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<functional>

using namespace std;

int debug  = 0;

int findkmissing(vector<int>& v, int i, int j, int k) {
	if (j < i) return -1;
	if (k <= 0) return -1;
	if (j == i) return v[i]+k;
	if (debug) { cout << "k:" << k << " " << i << "," << j << " ("; for(int t = i; t <=j; t++) cout << v[t] << " "; cout << ")" << endl; }
	if ((i+1) ==j) {
		int d = (v[j] - v[i]) - (j-i);
		if (d < k) {
		   k-=d;
		   return v[j]+k;
		} else {
		   return v[i]+k;
		}
	}
	//(i, m, j)
	int m = i + (j-i)/2;
        int d = v[m] - v[i] - (m - i);
        if (d >= k) {
		return findkmissing(v, i, m, k);
	} else {
		return findkmissing(v, m, j, k-d);
	}
}
int findkmissing(vector<int>& v, int k) {
	int sz = v.size();
	if (sz == 0) return -1;
	if (k <= 0) return -1;
	if (sz == 1) return v[0]+k;

	int i = 0;
	int j = sz - 1;
	int d;
#if 0
	d = v[j] - v[i] + 1;
	d -= sz; // 3
	if (d < k) {
		k-=d;
		return v[j]+k;
	}
#endif
	if (debug) { cout << "k:" << k << " " << i << "," << j << " ("; for(int t = i; t <=j; t++) cout << v[t] << " "; cout << ")" << endl;}
	while((i+1) < j) {
		int m = i + (j-i)/2;
		int d = v[m] - v[i] - (m - i);
	        if (d >= k) {
			j=m;
		}else {
			i=m;
			k-=d;
		}
		if (debug) { cout << "k:" << k << " " << i << "," << j << " ("; for(int t = i; t <=j; t++) cout << v[t] << " "; cout << ")" << endl; }
	}

	if (debug) { cout << "ans: i,j,k = " << i << ":" << v[i] << " " << j << ":" << v[j] << " "  << k << endl; }
	d = ((v[j]-v[i])-1);
	if (d < k) {
		k-=d;
		if (debug) { cout << "ans: i,j,k = " << i << ":" << v[i] << " " << j << ":" << v[j] << " "  << k << " " << v[j]+k << endl; }
		return v[j]+k;
	} else {
		if (debug) { cout << "ans: i,j,k = " << i << ":" << v[i] << " " << j << ":" << v[j] << " "  << k << " " << v[i]+k << endl; }
		return v[i]+k;
	}
}

int main(void) {
    vector<int> vec = {4,7,9,10,15,17};
    for(int n = 0; n <= vec.size(); n++) {
       vector<int> v(begin(vec), begin(vec)+n);
       for(auto x: v) cout << "[" << x << "] "; cout << endl;
       for(int k = 0; k < 2*n; ++k) {
        int ans1 = findkmissing(v,k);
        int ans2 = findkmissing(v, 0, n-1, k);
        if (ans1 != ans2)
          cout << "k:" << k << " ans:" << ans1 << " != " << ans2 << endl;
	else 
          cout << "k:" << k << " ans:" << ans1 << endl;
       }
    }
    return 0;
}


