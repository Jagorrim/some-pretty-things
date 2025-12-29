//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <numeric>
#include <iomanip>
#include <set>
#include <queue>
#include <unordered_map>
#include <iostream>
//#define map unordered_map
//#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

#define int long long
#define ld long double

using namespace std;
random_device lal;
mt19937 rnd(lal());

const static int inf = 1e18, mod = 1000000007;
const static ld pi = 3.141592653589793, eps = 0.000000000000000001;


int pow2(int power) {
	if (power == 0) { return 1; }
	return ((int)2) << (power - 1);
}

struct Edge {
	int v, w;
};


struct Req {
	int l, r, i;
};

const int up = ((int)1e5) + 2, block = 1500;
int t = 0;
vector<int> first(up), last(up), tin(up), tout(up);
vector<pair<int, int>> eu;
vector<bool> got(up);
vector<vector<Edge>>g(up);

void dfs(int pos, int par, int par_w) {
	tin[pos] = t;
	++t;
	first[pos] = eu.size();
	eu.push_back({ par_w, pos });

	for (Edge e : g[pos]) {
		if (e.v == par) { continue; }
		dfs(e.v, pos, e.w);
	}
	tout[pos] = t;
	++t;
	last[pos] = eu.size();
	eu.push_back({ par_w, pos });
}

bool comp1(Req f, Req s) {
	return f.l < s.l;
}

bool comp2(Req f, Req s) {
	return f.r < s.r;
}

bool is_par(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

struct MexSqrt {
	vector<vector<int>> bs;
	vector<int> filled;


	void build() {
		for (int i = 0; i < up; ++i) {
			if (bs.empty() || bs.back().size() == block) {
				bs.emplace_back();
				filled.push_back(0);
			}
			bs.back().emplace_back(0);
		}
	}

	int mex() {
		int ans = 0;
		for (int i = 0; i < bs.size(); ++i) {
			if (filled[i] == bs[i].size()) {
				ans += bs[i].size();
				continue;
			}
			for (int j = 0; j < bs[i].size(); ++j) {
				if (bs[i][j] == 0) {
					ans += j;
					break;
				}
			}
			break;
		}
		return ans;
	}

	void change(int num, int status) {
		if (num >= up) {
			return;
		}
		bs[num / block][num % block] += status;
		if (bs[num / block][num % block] == 1 && status == 1) {
			filled[num / block]++;
		}
		else if (bs[num / block][num % block] == 0 && status == -1) {
			filled[num / block]--;
		}
	}
}mx;


void calc(int start, int end) {
	for (int i = start; i <= end; i++) {
		if (got[eu[i].second]) {
			mx.change(eu[i].first, -1);
			got[eu[i].second] = false;
		}
		else {
			mx.change(eu[i].first, 1);
			got[eu[i].second] = true;
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	mx.build();
	for (int i = 0; i < n - 1; ++i) {
		int u, v, x;
		cin >> u >> v >> x;
		--u, --v;
		g[u].push_back({ v,x });
		g[v].push_back({ u,x });
	}
	vector<Req> rs;
	vector<int>ans(q);
	dfs(0, 0, up - 1);

	for (int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		if (a == b) {
			continue;
		}
		int l, r;
		if (is_par(a, b) || is_par(b, a)) {
			l = first[a], r = first[b];
			if (l > r) {
				swap(l, r);
			}
			++l;
		}
		else {
			if (tin[a] < tin[b]) {
				l = last[a], r = first[b];
			}
			else {
				l = last[b], r = first[a];
			}
		}
		if (l > r) { swap(l, r); }
		rs.push_back({l, r, i});
	}
	sort(rs.begin(), rs.end(), comp1);
	for (int i = 0; i < rs.size(); i += block) {
		sort(rs.begin() + i, rs.begin() + min(i + block, (int)rs.size()), comp2);
	}

	int cur_l = 0, cur_r = 0;
	got[eu[0].second] = true;
	mx.change(eu[0].first, 1);

	for (int i = 0; i < rs.size(); ++i) {
		if (rs[i].l < cur_l) {
			calc(rs[i].l, cur_l - 1);
		}

		if (cur_r < rs[i].r) {
			calc(cur_r + 1, rs[i].r);
		}

		if (cur_l < rs[i].l) {
			calc(cur_l, rs[i].l - 1);
		}

		if (rs[i].r < cur_r) {
			calc(rs[i].r + 1, cur_r);
		}
		cur_l = rs[i].l;
		cur_r = rs[i].r;

		ans[rs[i].i] = mx.mex();
	}
	for (int i : ans) { cout << i << '\n'; }
}
