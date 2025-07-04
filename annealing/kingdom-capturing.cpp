// task - https://informatics.msk.ru/mod/statements/view.php?id=1975&chapterid=518#1
#include <bits/stdc++.h>


#define int long long

using namespace std;
random_device lal;
mt19937 rnd(lal());
const static int inf = 1e18;

int check(vector<vector<int>> &g, vector<bool> &send) {
    vector<bool> used(g.size(), false);
    int count = 0;
    for (int i = 0; i < send.size(); ++i) {
        if (!send[i]) { continue; }
        if (!used[i]) { ++count; }
        used[i] = true;
        for (int j: g[i]) {
            if (!used[j]) { ++count; }
            used[j] = true;
        }
    }
    return count;
}

vector<bool> annealing(int n, int k, vector<vector<int>> &g) {
    vector<bool> send(n, false);
    for (int i = 0; i < k; ++i) { send[i] = true; }
    shuffle(send.begin(), send.end(), rnd);
    double best_res, cur_res, T = 1, num = 10'000, new_res;
    best_res = cur_res = check(g, send);
    for (int _ = 0; _ < 10'000; ++_) {
        if (best_res == n) {
            return send;
        }
        int i = rnd() % n, j = rnd() % n;
        while (send[i] == send[j] && k != n) { i = rnd() % n, j = rnd() % n; }
        swap(send[i], send[j]);
        new_res = check(g, send);
        if (new_res > cur_res) {
            cur_res = new_res;
            best_res = max(best_res, cur_res);
        } else {
            double chance = new_res / cur_res * T;
            double got = ((double) (rnd() % (int) num)) / num;
            if (got <= chance) {
                cur_res = new_res;
                best_res = max(best_res, cur_res);
            } else {
                swap(send[i], send[j]);
            }
        }
    }
    return {};
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    int status;
    vector<vector<int>> g_w(n), g_b(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> status;
            if (status == 1) {
                g_w[i].push_back(j), g_w[j].push_back(i);
            } else if (status == 2) {
                g_b[i].push_back(j), g_b[j].push_back(i);
            }
        }
    }
    for (int t = 0; t < 170; ++t) {
        auto res = annealing(n, k, g_w);
        if (!res.empty()) {
            cout << "1\n";
            vector<int> nums;
            for (int i = 0; i < n; ++i) { if (res[i]) { nums.push_back(i + 1); }}
            cout << nums.size() << '\n';
            for (int i: nums) { cout << i << ' '; }
            return 0;
        }
        res = annealing(n, k, g_b);
        if (!res.empty()) {
            cout << "2\n";
            vector<int> nums;
            for (int i = 0; i < n; ++i) { if (res[i]) { nums.push_back(i + 1); }}
            cout << nums.size() << '\n';
            for (int i: nums) { cout << i << ' '; }
            return 0;
        }
    }

    cout << 0;
}
