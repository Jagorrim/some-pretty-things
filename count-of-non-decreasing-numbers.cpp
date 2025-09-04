//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <bits/stdc++.h>

//#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

#define int long long
#define ld long double

using namespace std;
random_device lal;
mt19937 rnd(lal());

const static int inf = 1e18, mod = ((int) 1e9) + 7, p = 241;
const static ld pi = 3.141592653589793;

int pow2(int power) {
    if (power == 0) { return 1; }
    return ((int) 2) << (power - 1);
}

int f(string end) {
    vector<int> nums_end(end.size());
    for (int i = 0; i < nums_end.size(); ++i) {
        nums_end[i] = stoll(string(end.begin() + i, end.begin() + i + 1));
    }

    vector<vector<int>>
            dp(end.size() + 1, vector<int>(10, 0)),
            dp_edge(end.size() + 1, vector<int>(10, 0));
    for (int i = 1; i <= 9; ++i) {
        dp[1][i] = 1;
    }
    int res = 0;
    if (nums_end[0] != 0) { ++res; } // костыль для случая 0.

    // часть без ограничений (т.е. без самого крутого разряда)
    for (int cur_l = 1; cur_l < end.size() - 1; ++cur_l) {
        for (int i = 0; i <= 9; ++i) {
            for (int j = i; j <= 9; ++j) {
                dp[cur_l + 1][j] = (dp[cur_l + 1][j] + dp[cur_l][i]);
            }
        }
    }
    for (int cur_l = 1; cur_l < end.size(); ++cur_l) {
        for (int i = 0; i <= 9; ++i) {
            res = (res + dp[cur_l][i]);
        }
    }
    // часть с ограничениями
    dp = vector<vector<int>>(end.size() + 1, vector<int>(10, 0));
    for (int i = 1; i < nums_end[0]; ++i) {
        dp[1][i] = 1;
    }
    dp_edge[1][nums_end[0]] = 1;

    for (int cur_l = 1; cur_l < end.size(); ++cur_l) {
        for (int i = 0; i <= 9; ++i) {
            for (int j = i; j <= 9; ++j) {
                dp[cur_l + 1][j] = (dp[cur_l + 1][j] + dp[cur_l][i]);
            }
        }

        if (nums_end[cur_l] >= nums_end[cur_l - 1]) {
            dp_edge[cur_l + 1][nums_end[cur_l]] =
                    (dp_edge[cur_l + 1][nums_end[cur_l]] + dp_edge[cur_l][nums_end[cur_l - 1]]);
        }
        for (int i = nums_end[cur_l - 1]; i < nums_end[cur_l]; ++i) {
            dp[cur_l + 1][i] = (dp[cur_l + 1][i] + dp_edge[cur_l][nums_end[cur_l - 1]]);
        }
    }

    for (int i = 0; i <= 9; ++i) {
        res = (res + dp[end.size()][i]);
    }
    for (int i = 1; i < end.size(); ++i) {
        if (nums_end[i] < nums_end[i - 1]) {
            return res;
        }
    }
    res = (res + dp_edge[end.size()][nums_end[end.size() - 1]]);

    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string l, r;
    cin >> l >> r;
    int res = f(r) - f(l);
    vector<int> nums_end(l.size());
    for (int i = 0; i < nums_end.size(); ++i) {
        nums_end[i] = stoll(string(l.begin() + i, l.begin() + i + 1));
    }
    bool flag = true;
    for (int i = 1; i < l.size(); ++i) {
        if (nums_end[i] < nums_end[i - 1]) {
            flag = false;
        }
    }
    if (flag) { ++res; }
    cout << res % mod;
}
