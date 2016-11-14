#include <cassert>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

const int INF = 1000000000;
const int MAX_NODES = 1000 + 10;
const int MAX_MASK = 1024 + 10;

int dist[MAX_NODES][MAX_MASK], n, m, k, cti, a[MAX_NODES], x, y, z;
set<pair<int, pair<int, int> > > S;
vector<pair<int, int> > adj[MAX_NODES];
bool occurs[MAX_NODES];

inline void push (int vn, int vm, int vv) {
	if (dist[vn][vm] <= vv)
		return ;
	pair<int, pair<int, int> > mp = make_pair(dist[vn][vm], make_pair(vn, vm));
	if (S.find(mp) != S.end())
		S.erase(S.find(mp));
	dist[vn][vm] = vv;
	mp.first = vv;
	S.insert(mp);
}

int main () {
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin >> n >> m >> k;
    assert(2 <= n && n <= 1000);
    assert(1 <= m && m <= 2000);
    assert(1 <= k && k <= 10);
	for(int i = 1; i <= n; i++) {
		cin >> cti;
        assert(0 <= cti && cti <= k);
		for(int j = 1; j <= cti; j++) {
			cin >> x;
            assert(1 <= x && x <= k);
            assert((a[i] & (1 << (x - 1))) == 0);
			a[i] |= (1 << (x - 1));
		}
	}
    set<pair<int, int> > edges;
	for(int i = 1; i <= m; i++) {
		cin >> x >> y >> z;
        assert(1 <= x && x <= n);
        assert(1 <= y && y <= n);
        assert(1 <= z && z <= 10000);
        assert(x != y);
        edges.insert(make_pair(min(x, y), max(x, y)));
		adj[x].push_back(make_pair(y, z));
		adj[y].push_back(make_pair(x, z));
	}
    assert(edges.size() == m);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < (1 << k); j++)
			dist[i][j] = INF;
	push(1, a[1], 0);
	while (S.size() > 0) {
		int vn = S.begin()->second.first;
		int vm = S.begin()->second.second;
        occurs[vn] = true;
		S.erase(S.begin());
		for(int i = 0; i < adj[vn].size(); i++)
			push(adj[vn][i].first, vm | a[adj[vn][i].first], dist[vn][vm] + adj[vn][i].second);
	}
    for(int i = 1; i <= n; i++)
        assert(occurs[i]);
	int ret = INF;
	for(int i = 0; i < (1 << k); i++)
		for(int j = i; j < (1 << k); j++) if ((i | j) == ((1 << k) - 1))
			ret = min(ret, max(dist[n][i], dist[n][j]));
	cout << ret << endl;
	return 0;
}
