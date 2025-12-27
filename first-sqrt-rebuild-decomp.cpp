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
#include <unordered_set>
#include <iostream>
#define set unordered_set
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


struct Block {
	vector<int> items;
	int min = inf;
};
vector<Block> blocks{ };
int hm = 1200;

void rebuild() {
	vector<int> nums;
	for (auto b : blocks) {
		for (int j : b.items) {
			nums.push_back(j);
		}
	}
	blocks.clear();
	for (int i : nums) {
		if (blocks.empty() || blocks.back().items.size() >= hm) {
			blocks.emplace_back();
		}
		blocks.back().items.push_back(i);
		blocks.back().min = min(blocks.back().min, i);
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin >> n;
	char type;
	int j, x;
	cin >> type >> j >> x;
	blocks = { {{x}, x} };

	--n;
	for (int i = 0; i < n; ++i) {
		if (i % hm == 0) {
			rebuild();
		}
		char type;
		cin >> type;
		if (type == '?') {
			int l, r;
			cin >> l >> r;
			--l, --r;
			int ans = inf;
			int first = 0;
			for (auto& b : blocks) {
				int last = first + b.items.size() - 1;
				if (r < first) { break; }
				if (l > last) {
					first += b.items.size();
					continue;
				}
				if (l <= first && last <= r) {
					ans = min(ans, b.min);
				}
				else {
					for (int j = 0; j < b.items.size(); ++j) {
						if (l <= first + j && first + j <= r) {
							ans = min(ans, b.items[j]);
						}
					}
				}
				first += b.items.size();
			}
			cout << ans << '\n';
		}
		else {
			int j, x;
			cin >> j >> x;
			int last = 0;
			for (int k = 0; k < blocks.size(); ++k) {
				last += blocks[k].items.size();
				if (j <= last) {
					int first = last - blocks[k].items.size();
					blocks[k].items.insert(blocks[k].items.begin() + j - first, x);
					blocks[k].min = min(blocks[k].min, x);
					break;
				}
			}
		}
	}
}
