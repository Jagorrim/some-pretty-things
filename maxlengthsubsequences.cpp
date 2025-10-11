//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <random>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include <iostream>
//#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

#define int long long
#define ld long double

using namespace std;
random_device lal;
mt19937 rnd(lal());

const static int inf = 1e18, mod = 1000000007;
const static ld pi = 3.141592653589793, eps = 0.0000000001;

int pow2(int power) {
	if (power == 0) { return 1; }
	return ((int)2) << (power - 1);
}

int res = -1;

//const int sg_base = 4;
const int sg_base = 131072;

const int sg_size = sg_base * 2 - 1;
struct SG {
	struct Node {
		int l, r;
		int max_len = 0, max_sum = 0;
	} sg[sg_size];

	Node merge(Node f, Node s) {
		Node res;
		res.l = f.l, res.r = s.r;
		if (f.max_len > s.max_len) {
			res.max_len = f.max_len;
			res.max_sum = f.max_sum;
		}
		else if (f.max_len < s.max_len) {
			res.max_len = s.max_len;
			res.max_sum = s.max_sum;
		}
		else {
			res.max_len = f.max_len;
			res.max_sum = f.max_sum + s.max_sum;
		}
		res.max_sum %= mod;
		return res;
	}

	void build(int pos, int l, int r) {
		sg[pos].l = l, sg[pos].r = r;
		if (pos * 2 + 1 >= sg_size) { return; }
		int mid = (l + r) / 2;
		build(pos * 2 + 1, l, mid);
		build(pos * 2 + 2, mid, r);
	}

	void set(int pos, int i, int len, int sum) {
		if (sg[pos].l == i && sg[pos].r == i + 1) {
			if (sg[pos].max_len == len) {
				sg[pos].max_sum += sum;
			}
			else {
				sg[pos].max_len = len;
				sg[pos].max_sum = sum;
			}
			sg[pos].max_sum %= mod;

			return;
		}
		int mid = (sg[pos].l + sg[pos].r) / 2;
		if (i < mid) {
			set(pos * 2 + 1, i, len, sum);
		}
		else {
			set(pos * 2 + 2, i, len, sum);
		}
		sg[pos] = merge(sg[pos * 2 + 1], sg[pos * 2 + 2]);
	}

	Node sum(int pos, int l, int r) {
		if (sg[pos].l == l && sg[pos].r == r) {
			return sg[pos];
		}

		int mid = (sg[pos].l + sg[pos].r) / 2;
		if (l < mid && r <= mid) { return sum(pos * 2 + 1, l, r); }
		else if (l >= mid && r > mid) { return sum(pos * 2 + 2, l, r); }
		else {
			return merge(sum(pos * 2 + 1, l, mid), sum(pos * 2 + 2, mid, r));
		}
	}

}rsg;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	rsg.build(0, 0, sg_base);
	map<int, int> comp;
	int n;
	cin >> n;
	vector<int>a(n), b;
	for (int& i : a) { cin >> i; }
	b = a;
	sort(b.begin(), b.end());
	comp[b[0]] = 1;
	int cur = 1;
	for (int i = 1; i < n; ++i) {
		if (b[i] != b[i - 1]) {
			++cur;
			comp[b[i]] = cur;
		}
	}
	for (int i = 0; i < n; ++i) {
		int num = comp[a[i]];
		auto res = rsg.sum(0, 0, num);
		rsg.set(0, num, res.max_len + 1, res.max_sum + (int)(res.max_sum == 0));
	}
	int max_len = -1, ans = 0;
	for (int i = 1; i <= n; ++i) {
		max_len = max(max_len, rsg.sum(0, i, i + 1).max_len);
	}
	for (int i = 1; i <= n; ++i) {
		auto res = rsg.sum(0, i, i + 1);
		if (res.max_len == max_len) {
			ans += res.max_sum;
			ans %= mod;
		}
	}
	cout << ans;

}
