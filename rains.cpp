// task - https://codeforces.com/gym/105674/problem/C
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <bits/stdc++.h>

#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")
#define ll long long
using namespace std;
random_device lal;
//mt19937 rnd(lal());
mt19937 rnd(3423215);
const static ll inf = 1e18;


struct Treap {
    int sg_l, sg_r, size, y;

    Treap *l = 0, *r = 0;

    Treap(int sg_l, int sg_r, int size) : sg_l(sg_l), sg_r(sg_r), size(size), y(rnd() % 1'000'000'000) {}

    Treap() {}
};

int get_size(Treap *t) {
    if (!t) { return 0; }
    return t->size;
}

void upd(Treap *t) {
    if (!t) { return; }
    t->size = 1 + get_size(t->l) + get_size(t->r);
}

pair<Treap *, Treap *> split(Treap *t, int count) {
    if (!t) { return {0, 0}; }
    if (get_size(t->l) + 1 == count) {
        auto item = t->r;
        t->r = 0;
        upd(t);
        return {t, item};
    } else if (get_size(t->l) + 1 < count) {
        auto q = split(t->r, count - get_size(t->l) - 1);
        t->r = q.first;
        upd(t);
        return {t, q.second};
    } else {
        auto q = split(t->l, count);
        t->l = q.second;
        upd(t);
        return {q.first, t};
    }
}

Treap *merge(Treap *t1, Treap *t2) {
    if (!t1) { return t2; }
    if (!t2) { return t1; }
    if (t1->y > t2->y) {
        t1->r = merge(t1->r, t2);
        upd(t1);
        return t1;
    } else {
        t2->l = merge(t1, t2->l);
        upd(t2);
        return t2;
    }
}


Treap *min(Treap *t) {
    if (!t->l) { return t; }
    return min(t->l);
}


const static int sg_base = 131072;

struct SG {
    const static int sg_size = sg_base * 2 - 1;
    struct Node {
        int l, r, min, l_max, r_max, min_count;
        ll sum = 0, prev_min;
        int push = -1;
    } sg[sg_size];

    Node merge(Node f, Node s, vector<int> &a) {
        Node res;
        res.l = f.l, res.r = s.r;
        if (f.min < s.min) {
            res.min = f.min;
            res.min_count = f.min_count;
        } else {
            res.min = s.min;
            res.min_count = s.min_count;
            if (f.min == s.min) {
                res.min_count += f.min_count;
            }
        }

        res.prev_min = inf;
        for (ll i: {(ll) f.min, (ll) s.min, (ll) f.prev_min, (ll) s.prev_min}) {
            if (i == res.min) { continue; }
            if (res.prev_min > i) { res.prev_min = i; }
        }

        if (a[f.l_max] == a[s.l_max]) {
            res.l_max = f.l_max;
            res.r_max = s.r_max;
        } else if (a[f.l_max] > a[s.l_max]) {
            res.l_max = f.l_max;
            res.r_max = f.r_max;
        } else {
            res.l_max = s.l_max;
            res.r_max = s.r_max;
        }
        res.sum = f.sum + s.sum;
        return res;
    }

    void push_down(int pos) {
        if (pos * 2 + 1 >= sg_size || sg[pos].push == -1) { return; }
        int x = sg[pos].push;
        if (sg[pos * 2 + 1].min < x && x < sg[pos * 2 + 1].prev_min) {
            sg[pos * 2 + 1].sum += (ll) sg[pos * 2 + 1].min_count * (ll) (x - sg[pos * 2 + 1].min);
            sg[pos * 2 + 1].min = x;
            sg[pos * 2 + 1].push = x;
        }

        if (sg[pos * 2 + 2].min < x && x < sg[pos * 2 + 2].prev_min) {
            sg[pos * 2 + 2].sum += (ll) sg[pos * 2 + 2].min_count * (ll) (x - sg[pos * 2 + 2].min);
            sg[pos * 2 + 2].min = x;
            sg[pos * 2 + 2].push = x;
        }
        sg[pos].push = -1;
    }

    void build(int pos, int l, int r, vector<int> &a) {
        sg[pos].l = l, sg[pos].r = r;
        if (pos * 2 + 1 >= sg_size) {
            sg[pos].min = a[pos - a.size() + 1];
            sg[pos].min_count = 1;
            sg[pos].l_max = sg[pos].r_max = pos - a.size() + 1;
            sg[pos].prev_min = inf;
            return;
        }
        int mid = (l + r) / 2;
        build(pos * 2 + 1, l, mid, a);
        build(pos * 2 + 2, mid, r, a);
        sg[pos] = merge(sg[pos * 2 + 1], sg[pos * 2 + 2], a);
    }

    Node get_max(int pos, int l, int r, vector<int> &a) {
        if (sg[pos].l == l && sg[pos].r == r) {
            return sg[pos];
        }
        push_down(pos);
        int mid = (sg[pos].l + sg[pos].r) / 2;
        if (l < mid && r <= mid) {
            return get_max(pos * 2 + 1, l, r, a);
        } else if (l >= mid && r > mid) {
            return get_max(pos * 2 + 2, l, r, a);
        } else {
            return merge(
                    get_max(pos * 2 + 1, l, mid, a),
                    get_max(pos * 2 + 2, mid, r, a),
                    a
            );
        }
    }

    ll get_sum(int pos, int l, int r) {
        if (sg[pos].l == l && sg[pos].r == r) { return sg[pos].sum; }
        push_down(pos);
        int mid = (sg[pos].l + sg[pos].r) / 2;
        if (l < mid && r <= mid) { return get_sum(pos * 2 + 1, l, r); }
        else if (l >= mid && r > mid) { return get_sum(pos * 2 + 2, l, r); }
        else {
            return get_sum(pos * 2 + 1, l, mid) + get_sum(pos * 2 + 2, mid, r);
        }
    }


    void maximize(int pos, int l, int r, int x, vector<int> &a) {
        if (sg[pos].min >= x) { return; }

        if (sg[pos].l == l && sg[pos].r == r && x < sg[pos].prev_min) {
            sg[pos].push = x;
            sg[pos].sum += (ll) sg[pos].min_count * (ll) (x - sg[pos].min);
            sg[pos].min = x;
            return;
        }
        push_down(pos);
        int mid = (sg[pos].l + sg[pos].r) / 2;
        if (l < mid && r <= mid) {
            maximize(pos * 2 + 1, l, r, x, a);
        } else if (l >= mid && r > mid) {
            maximize(pos * 2 + 2, l, r, x, a);
        } else {
            maximize(pos * 2 + 1, l, mid, x, a);
            maximize(pos * 2 + 2, mid, r, x, a);
        }
        sg[pos] = merge(sg[pos * 2 + 1], sg[pos * 2 + 2], a);
    }
} rsg;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(sg_base);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    Treap *t = new Treap(0, 1, 1);
    for (int i = 1; i < n; ++i) {
        t = merge(t, new Treap(i, i + 1, 1));
    }
    rsg.build(0, 0, sg_base, a);
    int k;
    for (int i = 0; i < n - 1; ++i) {
        cin >> k;
        auto q = split(t, k);
        auto q2 = split(q.first, k - 1);
        auto item = min(q.second);

        auto res1 = rsg.get_max(0, q2.second->sg_l, q2.second->sg_r, a);
        auto res2 = rsg.get_max(0, item->sg_l, item->sg_r, a);

        item->sg_l = q2.second->sg_l;
        rsg.maximize(0, res1.l_max, res2.r_max, min(a[res1.l_max], a[res2.l_max]), a);
        cout << rsg.get_sum(0, item->sg_l, item->sg_r) << '\n';
        t = merge(q2.first, q.second);
    }
}
