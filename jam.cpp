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
#define map unordered_map
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

struct Req {
	int l, r, x, y, i;
};


signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	vector<int>a(n), b(n), ans(n, -1);
	for (int& i : a) { cin >> i; }
	for (int& i : b) { cin >> i; }
	for (int i = 0; i < n; ++i) {
		if (a[i] >= b[i]) { ans[i] = 0; }
	}
	int q, hm = 800;
	cin >> q;
	vector<vector<Req>> r;
	for (int i = 0; i < q; ++i) {
		if (r.empty() || r.back().size() > hm) {
			r.emplace_back();
		}
		r.back().emplace_back();
		cin >> r.back().back().l >> r.back().back().r >> r.back().back().x >> r.back().back().y;
		r.back().back().l--, r.back().back().r--;
	}
	int calced = 0;
	for (int i = 0; i < r.size(); ++i) {
		vector<int> start(n), d(n), d2(n);
		for (auto& j : r[i]) {
			start[j.l] += j.x;
			if (j.l + 1 < n) {
				d[j.l + 1] += j.y;
			}
			if (j.r + 1 < n) {
				start[j.r + 1] -= j.x;
				d[j.r + 1] -= j.y;
				d2[j.r + 1] -= j.y * (j.r - j.l);
			}
		}
		int val = 0, cur_d = 0;
		vector<int> ap = a;
		for (int i = 0; i < n; ++i) {
			val += start[i];
			ap[i] += val;
		}
		int hm = 0;
		for (int i = 0; i < n; ++i) {
			cur_d += d[i];
			hm += cur_d + d2[i];
			ap[i] += hm;
		}

		for (int k = 0; k < n; ++k) {
			if (ans[k] == -1 && ap[k] >= b[k]) {
				int add = 0;
				for (int k2 = 0; k2 < r[i].size(); ++k2) {
					auto j = r[i][k2];
					if (j.l <= k && k <= j.r) {
						add += j.x;
						add += (k - j.l) * j.y;
					}
					if (a[k] + add >= b[k]) {
						ans[k] = calced + k2 + 1;
						break;
					}
				}
			}
		}

		a = ap;
		calced += r[i].size();
	}

	for (int i : ans) { cout << i << ' '; }
}
