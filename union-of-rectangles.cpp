//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <random>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

#include <iostream>
//#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

#define ll long long
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

//const int sg_base = 8;
const ll sg_base = 2147483648;

struct SG {
	struct Node {
		ll l, r, min_count = 0;
		int min = 0, lc = -1, rc = -1, pos = -1;
		int push = 0;

		Node() {}
		Node(ll l, ll r, int min, ll min_count, int pos) :l(l), r(r), min(min), min_count(min_count), pos(pos) {}
	};

	Node merge(Node f, Node s) {
		Node res;
		res.l = f.l, res.r = s.r;
		res.lc = f.pos, res.rc = s.pos;

		if (f.min < s.min) {
			res.min = f.min;
			res.min_count = f.min_count;
		}
		else if (f.min > s.min) {
			res.min = s.min;
			res.min_count = s.min_count;
		}
		else {
			res.min = f.min;
			res.min_count = f.min_count + s.min_count;
		}
		return res;
	}

	vector<Node> sg;
	void add_c(int pos) {
		ll mid = (sg[pos].l + sg[pos].r) / 2;
		if (sg[pos].lc == -1) {
			sg[pos].lc = sg.size();
			sg.emplace_back(sg[pos].l, mid, 0, sg[pos].min_count / (ll)2, sg.size());
			sg[pos].rc = sg.size();
			sg.emplace_back(mid, sg[pos].r, 0, sg[pos].min_count / (ll)2, sg.size());
		}
	}
	void build() {
		sg.reserve(5e6);
		sg.emplace_back(0, sg_base, 0, sg_base, 0);
	}

	void push(int pos) {
		sg[sg[pos].lc].min += sg[pos].push;
		sg[sg[pos].rc].min += sg[pos].push;
		sg[sg[pos].lc].push += sg[pos].push;
		sg[sg[pos].rc].push += sg[pos].push;
                sg[pos].push=0;
	}

	void add(int pos, ll l, ll r, int x) {
		if (sg[pos].l == l && sg[pos].r == r) {
			sg[pos].min += x;
			sg[pos].push += x;
			return;
		}
		add_c(pos);
		push(pos);
		ll mid = (sg[pos].l + sg[pos].r) / 2;
		if (l < mid && r <= mid) {
			add(sg[pos].lc, l, r, x);
		}
		else if (l >= mid && r > mid) {
			add(sg[pos].rc, l, r, x);
		}
		else {
			add(sg[pos].lc, l, mid, x);
			add(sg[pos].rc, mid, r, x);
		}
		sg[pos] = merge(sg[sg[pos].lc], sg[sg[pos].rc]);
		sg[pos].pos = pos;
	}

	Node min_count(int pos, ll l, ll r) {
		if (sg[pos].l == l && sg[pos].r == r) {
			return sg[pos];
		}
		add_c(pos);
		push(pos);
		ll mid = (sg[pos].l + sg[pos].r) / 2;
		if (l < mid && r <= mid) {
			return min_count(sg[pos].lc, l, r);
		}
		else if (l >= mid && r > mid) {
			return min_count(sg[pos].rc, l, r);
		}
		else {
			return merge(min_count(sg[pos].lc, l, mid),
				min_count(sg[pos].rc, mid, r));
		}
	}
}rsg;

struct Event {
	int x, y1, y2, type;


	bool operator<(const Event other)const {
		if (this->x == other.x) { return this->type > other.type; }
		return this->x < other.x;
	}
};


signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	rsg.build();
	int n;
	cin >> n;
	vector<Event> e(2 * n);
	for (int i = 0; i < n; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		e[i] = { x1, y1, y2, 1 };
		e[i + n] = { x2, y1, y2, -1 };
	}
	sort(e.begin(), e.end());
	ll ans = 0, shift = 1e9;
	//shift = 0;
	for (int i = 0; i < 2 * n; ++i) {
		if (i != 0) {
			auto res = rsg.min_count(0, 0, sg_base);
			ans += (e[i].x - e[i - 1].x) * (sg_base - res.min_count);
		}
		if (e[i].y1 != e[i].y2) {
			rsg.add(0, e[i].y1 + shift, e[i].y2 + shift, e[i].type);
		}
	}
	cout << ans;

}
