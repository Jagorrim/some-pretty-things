// task - https://codeforces.com/gym/106180/problem/C

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <numeric>
#include <iomanip>
#include <set>

#include <iostream>
#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

#define ll long long
#define ld long double

using namespace std;
random_device lal;
mt19937 rnd(lal());

const static ll inf = 1e18, mod = 1000000009, base = 37;
const static ll  mod2 = 1000000007, base2 = 39;

const static ld pi = 3.141592653589793, eps = 0.0000000001;

int pow2(int power) {
	if (power == 0) { return 1; }
	return ((int)2) << (power - 1);
}
int up = 1e5 + 1;
vector<int> e(up);
vector<int>p;


vector<int> fact(int num) {
	vector<int> res;
	while (e[num] != 0) {
		res.push_back(e[num]);
		num /= e[num];
	}
	return res;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	vector<int> indexes(up);
	for (int i = 2; i < up; ++i) {
		if (!e[i]) {
			indexes[i] = p.size();
			p.push_back(i);
			for (int j = i; j < up; j += i) {
				e[j] = i;
			}
		}
	}
	int n;
	cin >> n;
	vector<int>a(n);
	for (int& i : a) { cin >> i; }

	vector<bool> pref(p.size()), pref2(p.size());
	map<int, int> poses, poses2;
	vector<int>ls(n, -1);
	set<int> rs;
	ll hash = 0, hash2 = 0;

	vector<ll> pows(p.size()), pows2(p.size());
	pows[0] = pows2[0] = 1;
	for (int i = 1; i < p.size(); ++i) {
		pows[i] = (pows[i - 1] * base) % mod;
		pows2[i] = (pows2[i - 1] * base2) % mod2;
	}
	for (int i = 0; i < p.size(); ++i) {
		hash += pows[i];
		hash %= mod;

		hash2 += pows2[i];
		hash2 %= mod2;
	}
	poses[hash] = poses2[hash2] = -1;
	for (int i = 0; i < n; ++i) {
		for (int num : fact(a[i])) {
			ll old_val = (((int)pref[indexes[num]]) + 1) * pows[indexes[num]];
			old_val %= mod;
			pref[indexes[num]] = pref[indexes[num]] ^ true;
			ll new_val = (((int)pref[indexes[num]]) + 1) * pows[indexes[num]];
			new_val %= mod;

			hash = (hash - old_val + mod + new_val) % mod;


			ll old_val2 = (((int)pref2[indexes[num]]) + 1) * pows2[indexes[num]];
			old_val2 %= mod2;
			pref2[indexes[num]] = pref2[indexes[num]] ^ true;
			ll new_val2 = (((int)pref2[indexes[num]]) + 1) * pows2[indexes[num]];
			new_val2 %= mod2;

			hash2 = (hash2 - old_val2 + mod2 + new_val2) % mod2;
		}
		if (poses.find(hash) != poses.end() && poses2.find(hash2) != poses2.end() && poses[hash] == poses2[hash2]) {
			int l = poses[hash] + 1;
			int r = i;
			ls[l] = r;
			rs.insert(r);
		}
		poses[hash] = i;

		poses2[hash2] = i;
	}
	int cur = 0, ans = 0;
	while (!rs.empty()) {
		int border = *rs.begin();
		rs.erase(rs.begin());
		for (int j = cur; j < border; ++j) {
			if (ls[j] != -1) {
				rs.erase(ls[j]);
			}
		}
		++ans;
		cur = border;
	}
	cout << ans + 1;
}
