//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <bits/stdc++.h>
#include <ext/rope>

#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

using namespace std;
using namespace __gnu_cxx;
random_device lal;
//mt19937 rnd(lal());
mt19937 rnd(2);

struct Treap {
    int x, y;
    Treap *l = 0, *r = 0;
    int size = 0;

    Treap(int x) : x(x), y(rnd() % 1'000'000), size(1) {}

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

pair<Treap *, Treap *> split(Treap *t, int count) {
    if (!t) { return {0, 0}; }
    if (get_size(t->l) + 1 == count) {
        auto new_item = t->r;
        t->r = 0;
        upd(t);
        return {t, new_item};
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


Treap *insert(Treap *t, int val, int i) {
    auto q = split(t, i);
    Treap *new_val = new Treap(val);
    return merge(merge(q.first, new_val), q.second);
}

Treap *del(Treap *t, int i) {
    auto q = split(t, i);
    auto q2 = split(q.first, i - 1);
    return merge(q2.first, q.second);
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, i, x;
    string o;
    cin >> n >> m >> x;
    int size = n;
    Treap *d = new Treap(x);
    for (int j = 0; j < n - 1; ++j) {
        cin >> x;
        d = insert(d, x, j + 1);
    }
    while (m--) {
        cin >> o;
        if (o == "add") {
            cin >> i >> x;
            ++size;
            if (size == 1) {
                d = new Treap(x);
            } else {
                d = insert(d, x, i);
            }
        } else {
            cin >> i;
            --size;
            if (i == 2) {
                int b = 2;
            }
            d = del(d, i);
        }
    }
    cout << size << '\n';
    for (int j = 0; j < size; ++j) {
        auto q = split(d, 1);
        cout << q.first->x << ' ';
        d = q.second;
    }
}
