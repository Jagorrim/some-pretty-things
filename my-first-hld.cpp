#include <iostream>
#include <bits/stdc++.h>
#include <ext/rope>

//#define int long long
using namespace std;
using namespace __gnu_cxx;

random_device rnd;
mt19937 lal(rnd());

int up_count = 20;
vector<vector<int>> up;
vector<int> tin, tout;
int t = 0;

struct Edge {
    int v;
    bool hv = false;

    Edge(int v) { this->v = v; }

    Edge() {}
};

bool is_parent(int a, int b) {
    return (tin[a] < tin[b] && tout[a] > tout[b]);
}

int lca(int a, int b) {
    if (is_parent(a, b)) { return a; }
    else if (a == b || is_parent(b, a)) { return b; }

    for (int i = up_count - 1; i >= 0; --i) {
        if (!is_parent(up[a][i], b)) {
            a = up[a][i];
        }
    }
    if (is_parent(a, b)) { return a; }
    return up[a][0];
}

void check1(int pos, int parent, vector<vector<Edge>> &g, vector<int> &sizes) {
    tin[pos] = ++t;
    if (parent != -1) {
        up[pos][0] = parent;
        for (int i = 1; i < up_count; ++i) {
            up[pos][i] = up[up[pos][i - 1]][i - 1];
        }
    }
    sizes[pos] = 1;
    for (Edge e: g[pos]) {
        if (e.v == parent) { continue; }
        check1(e.v, pos, g, sizes);
        sizes[pos] += sizes[e.v];
    }
    for (Edge &e: g[pos]) {
        if (sizes[e.v] >= sizes[pos] / 2) {
            e.hv = true;
            break;
        }
    }
    tout[pos] = ++t;
}

int counter = 0;

void get_order(int pos, int par, vector<vector<Edge>> &g, vector<bool> &used,
               vector<int> &parent, vector<int> &first, bool is_hv, vector<int> &poses, vector<int> &rev_poses) {
    used[pos] = true;
    if (is_hv) {
        first[pos] = first[par];
    } else { first[pos] = counter; }
    poses[pos] = counter;
    rev_poses[counter] = pos;
    ++counter;
    parent[pos] = par;
    for (Edge e: g[pos]) {
        if (used[e.v]) { continue; }
        if (e.hv) {
            get_order(e.v, pos, g, used, parent, first, true, poses, rev_poses);
            break;
        }
    }
    for (Edge e: g[pos]) {
        if (used[e.v]) { continue; }
        get_order(e.v, pos, g, used, parent, first, false, poses, rev_poses);
    }
}

const static int sg_base = 131072;
//const static int sg_base = 4;

struct SG {
    const static int sg_size = sg_base * 2 - 1;

    struct Node {
        int l, r, max = 0;
        Node() {}
    } sg[sg_size];

    void build(int pos, int l, int r) {
        sg[pos].l = l, sg[pos].r = r;
        if (pos * 2 + 1 >= sg_size) {
            return;
        }
        int mid = (l + r) / 2;
        build(pos * 2 + 1, l, mid);
        build(pos * 2 + 2, mid, r);
    }

    int get_max(int pos, int l, int r) {
        if (sg[pos].l == l && sg[pos].r == r) {
            return sg[pos].max;
        }
        int mid = (sg[pos].l + sg[pos].r) / 2;
        if (l < mid && r <= mid) { return get_max(pos * 2 + 1, l, r); }
        else if (l >= mid && r > mid) { return get_max(pos * 2 + 2, l, r); }
        else {
            return max(get_max(pos * 2 + 1, l, mid), get_max(pos * 2 + 2, mid, r));
        }
    }

    void upd_dot(int pos, int l, int r, int x) {
        if (sg[pos].l == l && sg[pos].r == r) {
            sg[pos].max += x;
            return;
        }
        int mid = (sg[pos].l + sg[pos].r) / 2;
        if (l < mid && r <= mid) {
            upd_dot(pos * 2 + 1, l, r, x);
        } else if (l >= mid && r > mid) {
            upd_dot(pos * 2 + 2, l, r, x);
        }
        sg[pos].max = max(sg[pos * 2 + 1].max, sg[pos * 2 + 2].max);
    }
} rsg;


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    tin.resize(n), tout.resize(n);
    up.resize(n, vector<int>(up_count, 0));
    vector<vector<Edge>> g(n);
    vector<int> sizes(n, 0), parent(n, -1), first(n), poses(n), rev_poses(n, -1);
    int u, v;
    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
        --u, --v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    check1(0, -1, g, sizes);
    vector<bool> used(n, false);
    get_order(0, -1, g, used, parent, first, false, poses, rev_poses);
    rsg.build(0, 0, sg_base);
    int q;
    char c;
    cin >> q;
    while (q--) {
        cin >> c >> u >> v;
        if (c == 'I') {
            rsg.upd_dot(0, poses[u - 1], poses[u - 1] + 1, v);
        } else {
            --u, --v;
            int l = lca(u, v);
            int answer = rsg.get_max(0, poses[l], poses[l] + 1);
            for (int cur: {u, v}) {
                while (cur >= 0 && poses[cur] > poses[l]) {
                    if (poses[l] > first[cur]) {
                        answer = max(answer, rsg.get_max(0, poses[l], poses[cur] + 1));
                        break;
                    } else {
                        answer = max(answer, rsg.get_max(0, first[cur], poses[cur] + 1));
                        cur = parent[rev_poses[first[cur]]];
                    }
                }
            }
            cout << answer << '\n';
        }
    }
}
