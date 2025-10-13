//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>

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

const static int sg_base = 131072;
//const static int sg_base = 4;

const static int sg_size = sg_base * 2 - 1;
vector<int> poses_, le_;
struct SG {
	struct Node {
		int l, r;
		int total = 0;
		int status = 0;
		vector<int> le;

		Node() { this->le.resize(26); }
	}sg[sg_size];

	void pull(int pos) {
		for (int i = 0; i < 26; ++i) {
			sg[pos].le[i] = sg[pos * 2 + 1].le[i] + sg[pos * 2 + 2].le[i];
		}
	}

	void build(int pos, int l, int r, string& s) {
		sg[pos].l = l, sg[pos].r = r;
		sg[pos].le = vector<int>(26);
		if (pos * 2 + 1 >= sg_size) {
			if (pos - sg_base + 1 < s.size()) {
				sg[pos].le[s[pos - sg_base + 1] - 'a']++;
				++sg[pos].total;
			}

			return;
		}
		int mid = (l + r) / 2;
		build(pos * 2 + 1, l, mid, s);
		build(pos * 2 + 2, mid, r, s);
		pull(pos);
		sg[pos].total = sg[pos * 2 + 1].total + sg[pos * 2 + 2].total;
	}

	void place(vector<int> poses, vector<int> le, int status) {
		if (status == -1) {
			reverse(poses.begin(), poses.end());
		}
		vector<int> counts(poses.size());
		for (int i = 0; i < poses.size(); ++i) {
			int pos = poses[i];
			counts[i] = sg[pos].total;
			sg[pos].le = vector<int>(26);
		}
		int cur = 0;
		for (int i = 0; i < poses.size(); ++i) {
			int pos = poses[i];
			while (true) {
				if (counts[i] > le[cur]) {
					counts[i] -= le[cur];
					sg[pos].le[cur] += le[cur];
					++cur;
				}
				else {
					sg[pos].le[cur] += counts[i];
					le[cur] -= counts[i];
					if (le[cur] == 0) { ++cur; }
					break;
				}
			}
		}
	}

	void push(int pos) {
		if (sg[pos].status == 0) { return; }
		sg[pos * 2 + 1].status = sg[pos * 2 + 2].status = sg[pos].status;
		place({ pos * 2 + 1, pos * 2 + 2 }, sg[pos].le, sg[pos].status);
		sg[pos].status = 0;
	}

	void sort(int pos, int l, int r, int status) {
		if (sg[pos].l == l && sg[pos].r == r) {
			poses_.push_back(pos);
			for (int i = 0; i < 26; ++i) {
				le_[i] += sg[pos].le[i];
			}
			sg[pos].status = status;
			return;
		}
		int mid = (sg[pos].l + sg[pos].r) / 2;
		push(pos);
		if (l < mid && r <= mid) {
			sort(pos * 2 + 1, l, r, status);
		}
		else if (l >= mid && r > mid) {
			sort(pos * 2 + 2, l, r, status);
		}
		else {
			sort(pos * 2 + 1, l, mid, status);
			sort(pos * 2 + 2, mid, r, status);
		}
	}

	void sort2(int pos, int l, int r) {
		if (sg[pos].l == l && sg[pos].r == r) {
			return;
		}
		int mid = (sg[pos].l + sg[pos].r) / 2;
		push(pos);
		if (l < mid && r <= mid) {
			sort2(pos * 2 + 1, l, r);
		}
		else if (l >= mid && r > mid) {
			sort2(pos * 2 + 2, l, r);
		}
		else {
			sort2(pos * 2 + 1, l, mid);
			sort2(pos * 2 + 2, mid, r);
		}
		pull(pos);
	}

	int got(int pos, int i) {
		if (sg[pos].l == i && sg[pos].r == i + 1) {
			for (int j = 0; j < 26; ++j) {
				if (sg[pos].le[j]) { return j; }
			}
		}
		push(pos);
		int mid = (sg[pos].l + sg[pos].r) / 2;
		if (i < mid) { return got(pos * 2 + 1, i); }
		else { return got(pos * 2 + 2, i); }
	}

}rsg;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, q;
	string s;
	cin >> n >> q >> s;
	rsg.build(0, 0, sg_base, s);
	while (q--) {
		int l, r, status;
		cin >> l >> r >> status;
		poses_ = {};
		le_ = vector<int>(26);
		if (status == 0) { status = -1; }
		rsg.sort(0, l - 1, r, status);
		rsg.place(poses_, le_, status);
		rsg.sort2(0, l - 1, r);
	}
	for (int i = 0; i < n; ++i) {
		cout << ((char)('a' + rsg.got(0, i)));
	}
}
