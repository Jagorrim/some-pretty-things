#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#include <bits/stdc++.h>
#include <ext/rope>

#pragma GCC target("avx,avx2,bmi,bmi2,fma,abm,mmx,popcnt,lzcnt,tune=native")

//#define int long long

using namespace std;
using namespace __gnu_cxx;
random_device lal;
mt19937 rnd(lal());
const static int inf = 1e9;


struct Card {
    int type, r, b;

    Card(int type, int r, int b) : type(type), r(r), b(b) {}
};

int calc(vector<int> &p, vector<Card> &cards) {
    int answer = 0;
    int r_card = 0, b_card = 0, r_piece = 0, b_piece = 0;
    for (int i: p) {
        int r_cost = max(cards[i].r - r_card, (int) 0);
        int b_cost = max(cards[i].b - b_card, (int) 0);
        int count = max(max(r_cost - r_piece, (int) 0), max(b_cost - b_piece, (int) 0));
        r_piece += count, b_piece += count;
        answer += count;
        ++answer;
        r_piece -= r_cost, b_piece -= b_cost;
        if (cards[i].type == 0) { ++r_card; }
        else { ++b_card; }
    }
    return answer;
}


int annealing(int n, vector<Card> &cards) {
    double best_res, cur_res, new_res;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) { p[i] = i; }
    shuffle(p.begin(), p.end(), rnd);
    best_res = cur_res = calc(p, cards);
    double T = 1;
    double num = 10'000;
    int up = 7000;
    for (int _ = 0; _ < up; ++_) {
        int i = rnd() % n, j = rnd() % n;
        while (n != 1 && i == j) {
            i = rnd() % n, j = rnd() % n;
        }
        swap(p[i], p[j]);
        new_res = calc(p, cards);
        if (new_res < cur_res) {
            cur_res = new_res;
            best_res = min(best_res, cur_res);
        } else {
            double chance = exp(cur_res - new_res) * T;
            double real = ((double) (rnd() % (int) num)) / num;
            if (real <= chance) {
                cur_res = new_res;
                best_res = min(best_res, cur_res);
            } else {
                swap(p[i], p[j]);
            }
        }
        T *= 0.99;
    }

    return best_res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<Card> cards;
    int r, b;
    char t;
    for (int i = 0; i < n; ++i) {
        cin >> t >> r >> b;
        if (t == 'R') {
            cards.emplace_back(0, r, b);
        } else {
            cards.emplace_back(1, r, b);
        }
    }
    int best_res = inf;
    for (int i = 0; i < 1500; ++i) {
        best_res = min(best_res, annealing(n, cards));
    }
    cout << best_res;

}