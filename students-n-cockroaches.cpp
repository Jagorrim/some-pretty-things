#include <bits/stdc++.h>

#define int long long
using namespace std;


struct Node {
    int sum = 0, l, r, a0, d, decrease = 0;
};


int lc(int pos) {
    return pos * 2 + 1;
}

int rc(int pos) {
    return pos * 2 + 2;
}


void build(int pos, vector<Node> &sg, int l, int r) {
    sg[pos].l = l, sg[pos].r = r;
    if (lc(pos) >= sg.size()) { return; }
    int mid = (l + r) / 2;
    build(lc(pos), sg, l, mid);
    build(rc(pos), sg, mid, r);
}

void sgpush(int pos, vector<Node> &sg) {
    if (lc(pos) >= sg.size()) {
        sg[pos].decrease = sg[pos].d = sg[pos].a0 = 0;
        return;
    }
    int la0 = sg[pos].a0;
    int l_sum = (la0 + la0 + sg[pos].d * ((sg[pos].r - sg[pos].l) / 2 - 1)) * (sg[pos].r - sg[pos].l) / 2 / 2;
    int ra0 = (sg[pos].a0 + (sg[pos].r - sg[pos].l) / 2 * sg[pos].d);
    int r_sum = (ra0 + ra0 + sg[pos].d * ((sg[pos].r - sg[pos].l) / 2 - 1)) * (sg[pos].r - sg[pos].l) / 2 / 2;
    sg[lc(pos)].sum += l_sum;
    sg[rc(pos)].sum += r_sum;

    sg[lc(pos)].sum += sg[pos].decrease * (sg[pos].r - sg[pos].l) / 2;
    sg[rc(pos)].sum += sg[pos].decrease * (sg[pos].r - sg[pos].l) / 2;

    sg[lc(pos)].a0 += sg[pos].a0;
    sg[rc(pos)].a0 += ra0;

    sg[lc(pos)].d += sg[pos].d;
    sg[rc(pos)].d += sg[pos].d;

    sg[lc(pos)].decrease += sg[pos].decrease;
    sg[rc(pos)].decrease += sg[pos].decrease;

    sg[pos].decrease = sg[pos].d = sg[pos].a0 = 0;
}


void add_progr(int pos, vector<Node> &sg, int l, int r, int a0, int d) {
    if (sg[pos].l == l && sg[pos].r == r) {
        sg[pos].a0 += a0;
        sg[pos].d += d;

        sg[pos].sum += (a0 + a0 + (r - l - 1) * d) * (r - l) / 2;

        return;
    }
    sgpush(pos, sg);
    int mid = (sg[pos].l + sg[pos].r) / 2;
    if (l < mid && r <= mid) {
        add_progr(lc(pos), sg, l, r, a0, d);
    } else if (l >= mid && r > mid) {
        add_progr(rc(pos), sg, l, r, a0, d);
    } else if (l < mid && r > mid) {
        add_progr(lc(pos), sg, l, mid, a0, d);
        add_progr(rc(pos), sg, mid, r, a0 + (mid - l) * d, d);
    }
    sg[pos].sum = sg[lc(pos)].sum + sg[rc(pos)].sum;

}


void decrease(int pos, vector<Node> &sg, int l, int r, int x) {
    if (sg[pos].l == l && sg[pos].r == r) {
        sg[pos].decrease += x;
        sg[pos].sum += (sg[pos].r - sg[pos].l) * x;
        return;
    }
    sgpush(pos, sg);
    int mid = (sg[pos].l + sg[pos].r) / 2;
    if (l < mid && r <= mid) {
        decrease(lc(pos), sg, l, r, x);
    } else if (l >= mid && r > mid) {
        decrease(rc(pos), sg, l, r, x);
    } else if (l < mid && r > mid) {
        decrease(lc(pos), sg, l, mid, x);
        decrease(rc(pos), sg, mid, r, x);
    }
    sg[pos].sum = sg[lc(pos)].sum + sg[rc(pos)].sum;
}

int get_sum(int pos, vector<Node> &sg, int l, int r) {
    if (sg[pos].l == l && sg[pos].r == r) {
        return sg[pos].sum;
    }
    sgpush(pos, sg);
    int mid = (sg[pos].l + sg[pos].r) / 2;
    if (l < mid && r <= mid) {
        return get_sum(lc(pos), sg, l, r);
    } else if (l >= mid && r > mid) {
        return get_sum(rc(pos), sg, l, r);
    } else if (l < mid && r > mid) {
        return get_sum(lc(pos), sg, l, mid) +
               get_sum(rc(pos), sg, mid, r);
    }
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    int asize = (int) pow(2, ceil(log2(n)));
    vector<Node> sg(asize * 2 - 1);
    build(0, sg, 0, asize);

    char req;
    int l, r, i, q, x;
    while (m--) {
        cin >> req;
        if (req == '?') {
            cin >> l >> r;
            cout << get_sum(0, sg, l - 1, r) << '\n';
        } else if (req == 'R') {

            cin >> i >> q;
            --i;
            int a0, a1;
            if (0 >= i - q + 1) {
                l = 0;
                a0 = q - i;
            } else {
                l = i - q + 1;
                a0 = 1;
            }

            a1 = q - 1;
            r = min(n, i + q);
            add_progr(0, sg, l, i + 1, a0, 1);
            if (i + 1 < n) {
                add_progr(0, sg, i + 1, r, a1, -1);
            }
        } else if (req == 'C') {
            cin >> l >> r >> x;
            decrease(0, sg, l - 1, r, -x);
        }
    }

    return 0;
}
