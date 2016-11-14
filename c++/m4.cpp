#define N 5000
#define K 5000
int n,k;
int x[N];  //xi [1 to 10^6]
int w[N];  //wi [1 to 10^6]
uint64_t xw[N]; 
uint64_t sw[N]; //sum weight so far from x[0].
int c[K];  //ci centroid 
int nc[K]; // next centroid
short cc[N]; //map i to j
uint64_t ans[K], tans = 0;  //ans: cost for each centroid, tans: total cost.
uint64_t tw=0;//total weight
uint64_t ts=0;//total sum
vector<bool> dmap(K, false);
