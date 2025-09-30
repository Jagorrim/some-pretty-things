//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
//#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

#define int long long
#define ld double

using namespace std;
random_device lal;
mt19937 rnd(lal());

const static int inf = 1e18, mod = 1000003999;
const static ld pi = 3.141592653589793, eps = 0.0000000001;

int pow2(int power) {
	if (power == 0) { return 1; }
	return ((int)2) << (power - 1);
}
struct Edge {
	int u, v, i;
};

vector<int> min_h, h;
vector<bool> used;
vector<vector<Edge>> g;
vector<vector<int>> ge;

void dfs(int pos, Edge par_e) {
	used[pos] = true;
	if (par_e.u != -1) {
		min_h[pos] = h[pos] = h[par_e.u] + 1;
	}

	for (Edge e : g[pos]) {
		if (e.i == par_e.i) { continue; }
		if (!used[e.v]) {
			dfs(e.v, e);		
			min_h[pos] = min(min_h[pos], min_h[e.v]);
		}
		else {
			min_h[pos] = min(min_h[pos], h[e.v]);
		}
	}
}

void dfs2(int pos, Edge par_e) {
	used[pos] = true;

	for (Edge e : g[pos]) {
		if (e.i == par_e.i) { continue; }
		if (par_e.i != -1 && min_h[e.v] < h[pos] && used[e.v]) {
			ge[par_e.i].push_back(e.i);
			ge[e.i].push_back(par_e.i);
		}
		if (!used[e.v]) { dfs2(e.v, e); }
	}
}

vector<int> colors;
int cur = 0;
void dfs3(int pos) {
	used[pos] = true;
	colors[pos] = cur;
	for (int i : ge[pos]) {
		if (!used[i]) { dfs3(i); }
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	g.resize(n);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back({ a,b,i }), g[b].push_back({ b, a,i });
	}
	used.resize(n), h.resize(n), min_h.resize(n), colors.resize(m), ge.resize(m);
	for (int i = 0; i < n; ++i) {
		if (!used[i]) {
			dfs(i, { -1,-1,-1 });
		}
	}
	used = vector<bool>(n);
	for (int i = 0; i < n; ++i) {
		if (!used[i]) {
			dfs2(i, { -1, -1, -1 });
		}
	}
	used = vector<bool>(m);
	colors.resize(m);
	for (int i = 0; i < m; ++i) {
		if (!used[i]) {
			++cur;
			dfs3(i);
		}
	}
	cout << cur << '\n';
	for (int i : colors) { cout << i << ' '; }

}
