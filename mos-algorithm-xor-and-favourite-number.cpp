// task - https://codeforces.com/contest/617/problem/E
//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <bits/stdc++.h>
#include <ext/rope>

#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

#define int long long

using namespace std;
using namespace __gnu_cxx;
random_device lal;
mt19937 rnd(lal());
const static int inf = 1e9;

struct Req {
    int l, r, index;

    Req(int l, int r, int index) : l(l), r(r), index(index) {}

    Req() {}
};

bool comp1(Req f, Req s) {
    return f.l < s.l;
}

bool comp2(Req f, Req s) {
    return f.r < s.r;
}

const static int counts_size = 1048580;

int counts[counts_size];
bool used[counts_size];


void up_r(int cur_r, int req_r, int k, int &answer, vector<int> &pref_xor) {
    for (int i = cur_r + 1; i <= req_r; ++i) {
        answer += counts[pref_xor[i + 1] ^ k];
        ++counts[pref_xor[i + 1]];
    }
}

void down_r(int cur_r, int req_r, int k, int &answer, vector<int> &pref_xor) {
    for (int i = cur_r; i > req_r; --i) {
        --counts[pref_xor[i + 1]];
        answer -= counts[pref_xor[i + 1] ^ k];
    }
}


void up_l(int cur_l, int req_l, int k, int &answer, vector<int> &pref_xor) {
    for (int i = cur_l - 1; i < req_l; ++i) {
        --counts[pref_xor[i + 1]];
        answer -= counts[pref_xor[i + 1] ^ k];
    }
}

void down_l(int cur_l, int req_l, int k, int &answer, vector<int> &pref_xor) {
    for (int i = cur_l - 2; i >= req_l; --i) {
        answer += counts[pref_xor[i + 1] ^ k];
        ++counts[pref_xor[i + 1]];
    }
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < counts_size; ++i) { counts[i] = 0, used[i] = false; }
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), pref_xor(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pref_xor[i + 1] = pref_xor[i] ^ a[i];
    }
    vector<Req> reqs;
    int l, r;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        --l, --r;
        reqs.emplace_back(l, r, i);
    }
    sort(reqs.begin(), reqs.end(), comp1);
    int start = 0;
    int m_sqrt = sqrt(m);
    for (int i = 0; i < 2 * m_sqrt + 2; ++i) {
        if (start >= m) { break; }
        if (start + m_sqrt >= m) {
            sort(reqs.begin() + start, reqs.begin() + m, comp2);
            break;
        } else {
            sort(reqs.begin() + start, reqs.begin() + start + m_sqrt, comp2);
            start += m_sqrt;
        }
    }
    l = reqs[0].l, r = reqs[0].r;
    counts[pref_xor[l]] = 1;
    int answer = 0;
    up_r(l - 1, r, k, answer, pref_xor);
    vector<int> res(m);
    res[reqs[0].index] = answer;
    for (int ri = 1; ri < m; ++ri) {
        Req req = reqs[ri];
        if (req.r > r) {
            up_r(r, req.r, k, answer, pref_xor);
        } else if (req.r < r) {
            down_r(r, req.r, k, answer, pref_xor);
        }
        if (req.l > l) {
            up_l(l, req.l, k, answer, pref_xor);
            answer += counts[pref_xor[req.l] ^ k];
            ++counts[pref_xor[req.l]];
        } else if (req.l < l) {
            down_l(l, req.l, k, answer, pref_xor);
            answer += counts[pref_xor[req.l] ^ k];
            ++counts[pref_xor[req.l]];
        }
        l = req.l, r = req.r;
        res[reqs[ri].index] = answer;
    }
    for (int i: res) { cout << i << '\n'; }
}
