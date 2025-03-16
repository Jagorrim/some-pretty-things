#include <bits/stdc++.h>

#define int long long
using namespace std;
int s;
bool is_find = false;
vector<int> tens{1};
//task - https://codeforces.com/gym/104949/problem/3
struct Numndata {
    int num, to_get;

    Numndata(int num) {
        this->num = num;
    }

    bool operator<(const Numndata &other) const {
        return this->num < other.num;
    }
};

void get_every_sum(vector<int> &columns, int pos, Numndata &lal, set<Numndata> &got, int half) {
    if (pos < half) {
        int val = tens[columns.size() - pos - 1];
        lal.to_get += val;
        get_every_sum(columns, pos + 1, lal, got, half);
        lal.to_get -= val;
        lal.num += columns[pos];
        get_every_sum(columns, pos + 1, lal, got, half);
        lal.num -= columns[pos];
    } else {
        got.insert(lal);
    }
}

void get_every_sum2(vector<int> &columns, vector<bool> &used_rows,
                    int pos, Numndata &lal, set<Numndata> &got, int half) {
    if (is_find) { return; }
    if (pos < columns.size()) {
        int val = tens[columns.size() - pos - 1];
        lal.to_get += val;
        get_every_sum2(columns, used_rows, pos + 1, lal, got, half);
        lal.to_get -= val;
        lal.num += columns[pos];
        get_every_sum2(columns, used_rows, pos + 1, lal, got, half);
        lal.num -= columns[pos];
    } else {
        auto found = got.find(s - lal.num);
        if (found != got.end()) {
            cout << "YES\n";
            is_find = true;
            int k = 0;
            for (int i: used_rows) { k += (int) i; }
            int half2 = half;
            if (columns.size() % 2 == 1) { ++half2; }
            string used = to_string(found->to_get + lal.to_get);
            vector<int> cols_used;
            for (int i = used.size() - 1; i > -1; --i) {
                if (used[i] == '1') {
                    ++k;
                    cols_used.push_back(columns.size() - used.size() + i + 1);
                }
            }
            cout << k << '\n';
            for (int i = 0; i < used_rows.size(); ++i) {
                if (used_rows[i]) {
                    cout << "1 " << i + 1 << '\n';
                }
            }
            for (int i: cols_used) {
                cout << "2 " << i << '\n';

            }

            return;
        }
    }
}

void solve(vector<vector<int>> &a, vector<int> &columns, vector<bool> &used_rows, int pos, int total_sum) {
    if (is_find) { return; }
    if (pos < used_rows.size() && total_sum > s) {
        solve(a, columns, used_rows, pos + 1, total_sum);
        if (is_find) { return; }
        used_rows[pos] = true;
        for (int j = 0; j < a[0].size(); ++j) {
            columns[j] -= a[pos][j];
            total_sum -= a[pos][j];
        }
        if (total_sum >= s) {
            solve(a, columns, used_rows, pos + 1, total_sum);
        }
        if (is_find) { return; }
        for (int j = 0; j < a[0].size(); ++j) {
            columns[j] += a[pos][j];
            total_sum += a[pos][j];
        }
        used_rows[pos] = false;
    } else {
        if (total_sum < s) { return; }
        int half = columns.size() / 2;

        set<Numndata> got;
        vector<bool> used(columns.size(), false);
        Numndata lal(0);
        lal.to_get = 0;
        get_every_sum(columns, 0, lal, got, half);
        get_every_sum2(columns, used_rows, half, lal, got, half);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int h, w;
    cin >> h >> w;
    for (int i = 0; i < 16; ++i) {
        tens.push_back(tens.back() * 10);
    }
    vector<bool> used_rows(h);
    vector<int> columns(w);
    int total_sum = 0;
    vector<vector<int>> a(h, vector<int>(w));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> a[i][j];
            total_sum += a[i][j];
            columns[j] += a[i][j];
        }
    }
    cin >> s;
    solve(a, columns, used_rows, 0, total_sum);
    if (!is_find) {
        cout << "NO";
    }
    return 0;
}
