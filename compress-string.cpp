//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <numeric>
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



struct Res {
	string word, res;
	int word_count = 0;
	int ans;
};

Res min(Res f, Res s) {
	if (f.ans == s.ans) {
		if (f.res < s.res) { return f; }
		return s;
	}
	if (f.ans < s.ans) { return f; }
	return s;
}


void recalc(int l, int r, int f, vector<vector<Res>>& dp_m, Res& first, Res& second) {
	if (first.word != second.word) {
		return;
	}
	if (dp_m[l][r].word_count == 1) {
		dp_m[l][r].ans = first.word.size() + to_string(first.word_count + second.word_count).size() + 2;
		dp_m[l][r].word = first.word;
		dp_m[l][r].word_count = first.word_count + second.word_count;
		dp_m[l][r].res = to_string(first.word_count + second.word_count) + '(' + dp_m[l][r].word + ')';
		return;
	}

	int count = first.word.size() + 2 + to_string(first.word_count + second.word_count).size();
	if (count < dp_m[l][r].ans ||
		count == dp_m[l][r].ans && to_string(first.word_count + second.word_count) + '(' + dp_m[l][r].word + ')' < dp_m[l][r].res) {
		dp_m[l][r].ans = count;
		dp_m[l][r].word = first.word;
		dp_m[l][r].word_count = first.word_count + second.word_count;
		dp_m[l][r].res = to_string(first.word_count + second.word_count) + '(' + dp_m[l][r].word + ')';
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string s;
	cin >> s;
	int n = s.size();
	vector<vector<Res>> dp(n, vector<Res>(n)), dp_m(n, vector<Res>(n));
	for (int i = 0; i < n; ++i) {
		dp[i][i].word = dp[i][i].res = string(s.begin() + i, s.begin() + i + 1);
		dp[i][i].word_count = dp[i][i].ans = 1;

		dp_m[i][i].word = dp_m[i][i].res = string(s.begin() + i, s.begin() + i + 1);
		dp_m[i][i].word_count = dp_m[i][i].ans = 1;
	}

	for (int len = 2; len <= n; ++len) {
		for (int l = 0; l < n - len + 1; ++l) {
			int r = l + len - 1;

			dp[l][r].ans = r - l + 1;
			dp[l][r].word_count = 1;
			dp[l][r].res = dp[l][r].word = string(s.begin() + l, s.begin() + r + 1);

			dp_m[l][r].ans = r - l + 1;
			dp_m[l][r].word_count = 1;
			dp_m[l][r].res = dp_m[l][r].word = string(s.begin() + l, s.begin() + r + 1);

			for (int f = l; f <= r - 1; ++f) {
				auto li = min(dp[l][f], dp_m[l][f]);
				auto ri = min(dp[f + 1][r], dp_m[f + 1][r]);

				if (li.ans + ri.ans < dp[l][r].ans || li.ans + ri.ans == dp[l][r].ans && li.res + ri.res < dp[l][r].res) {
					dp[l][r].ans = li.ans + ri.ans;
					dp[l][r].word = li.res + ri.res;
					dp[l][r].word_count = 1;
					dp[l][r].res = li.res + ri.res;
				}
				recalc(l, r, f, dp_m, dp[l][f], dp[f + 1][r]);
				recalc(l, r, f, dp_m, dp[l][f], dp_m[f + 1][r]);
				recalc(l, r, f, dp_m, dp_m[l][f], dp[f + 1][r]);
				recalc(l, r, f, dp_m, dp_m[l][f], dp_m[f + 1][r]);
			}
		}
	}
	if (dp[0][n - 1].res.size() == dp_m[0][n - 1].res.size()) {
		cout << min(dp[0][n - 1].res, dp_m[0][n - 1].res);
	}
	else if (dp[0][n - 1].res.size() < dp_m[0][n - 1].res.size()) {
		cout << dp[0][n - 1].res;
	}
	else {
		cout << dp_m[0][n - 1].res;

	}
	//cout << dp[0][n - 1].res << ' ' << dp_m[0][n - 1].res;
	//cout << min(dp[0][n - 1].res, dp_m[0][n - 1].res);

}
