// problem - https://informatics.msk.ru/mod/statements/view.php?id=1975&chapterid=2530#1
#include <bits/stdc++.h>


#define int long long

using namespace std;
random_device lal;
mt19937 rnd(lal());
const static int inf = 1e18;

struct Edge {
    int a, b, id;

    Edge(int a, int b, int id) : a(a), b(b), id(id) {}

    Edge() {}
};

int change_pos(vector<vector<Edge>> &g, int pos, vector<int> &id_used, int mode) {
    int counter = 0;
    for (Edge &e: g[pos]) {
        if (mode == 1) {
            if (id_used[e.id] == 0) { ++counter; }
            ++id_used[e.id];
        } else {
            if (id_used[e.id] == 1) { ++counter; }
            --id_used[e.id];
        }
    }
    return counter;
}


vector<bool> annealing(int n, int m, int k, vector<vector<Edge>> &g) {
    vector<bool> send(n, false);
    vector<int> id_used(m, 0);
    for (int i = 0; i < k; ++i) { send[i] = true; }
    shuffle(send.begin(), send.end(), rnd);
    double best_res, cur_res = 0, T = 1, num = 10'000, new_res;
    for (int i = 0; i < n; ++i) {
        if (!send[i]) { continue; }
        cur_res += change_pos(g, i, id_used, 1);
    }
    best_res = cur_res;
    for (int _ = 0; _ < 20'000; ++_) {
        if (best_res == m) {
            return send;
        }
        int i = rnd() % n, j = rnd() % n;
        while (send[i] == send[j]) { i = rnd() % n, j = rnd() % n; }
        if (!send[i] && send[j]) {
            swap(i, j);
        }
        new_res = cur_res;
        new_res -= change_pos(g, i, id_used, -1);
        swap(send[i], send[j]);
        new_res += change_pos(g, j, id_used, 1);
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
                change_pos(g, i, id_used, 1);
                change_pos(g, j, id_used, -1);
            }
        }
        T *= 0.99;
    }
    return {};
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<Edge>> g(n);
    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        --a, --b;
        g[a].emplace_back(a, b, i), g[b].emplace_back(b, a, i);
    }
    if (k == n) {
        cout << "Yes\n";
        for (int i = 1; i <= n; ++i) { cout << i << ' '; }
        return 0;
    }
    for (int t = 0; t < 350; ++t) {
        auto res = annealing(n, m, k, g);
        if (!res.empty()) {
            cout << "Yes\n";
            for (int i = 0; i < n; ++i) {
                if (res[i]) { cout << i + 1 << ' '; }
            }
            return 0;
        }
    }
    cout << "No";
}
