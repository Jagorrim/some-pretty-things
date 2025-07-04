// task - https://codeforces.com/gym/102936/problem/7
#include <bits/stdc++.h>
#include <ext/rope>


#define int long long

using namespace std;
using namespace __gnu_cxx;
random_device lal;
mt19937 rnd(lal());


int get_point_count(int i, int j, vector<vector<int>> &t) {
    int answer = 0;
    for (int y1 = 0; y1 < i; ++y1) {
        for (int x1 = 0; x1 < j; ++x1) {
            answer += (int) (t[y1][x1] == t[y1][j] && t[y1][j] == t[i][j] && t[i][j] == t[i][x1]);
        }
    }
    for (int y1 = i + 1; y1 < t.size(); ++y1) {
        for (int x1 = 0; x1 < j; ++x1) {
            answer += (int) (t[y1][x1] == t[y1][j] && t[y1][j] == t[i][j] && t[i][j] == t[i][x1]);
        }
    }
    for (int y1 = 0; y1 < i; ++y1) {
        for (int x1 = j + 1; x1 < t[0].size(); ++x1) {
            answer += (int) (t[y1][x1] == t[y1][j] && t[y1][j] == t[i][j] && t[i][j] == t[i][x1]);
        }
    }
    for (int y1 = i + 1; y1 < t.size(); ++y1) {
        for (int x1 = j + 1; x1 < t[0].size(); ++x1) {
            answer += (int) (t[y1][x1] == t[y1][j] && t[y1][j] == t[i][j] && t[i][j] == t[i][x1]);
        }
    }
    return answer;
}

pair<int, int> gen_cord(vector<vector<int>> &t) {
    int n = t.size(), m = t[0].size();
    return {rnd() % n, rnd() % m};
}

bool annealing(int n, int m, int c) {
    vector<vector<int>> t(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            t[i][j] = ((i * m) + j) % c;
        }
    }
    double total_count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            total_count += get_point_count(i, j, t);
        }
    }
    double T = 1;
    double num = 100'000;
    int up = (1e4);
    for (int hm = 0; hm < up; ++hm) {
        if (total_count == 0) {
            for (auto &i: t) {
                for (int j: i) {
                    cout << j + 1 << ' ';
                }
                cout << '\n';
            }
            return true;
        }
        auto [y1, x1] = gen_cord(t);
        int old_val = t[y1][x1];
        double old_count = get_point_count(y1, x1, t);
        t[y1][x1] = rnd() % c;
        double new_count = get_point_count(y1, x1, t);
        if (new_count < old_count) {
            total_count = total_count - (old_count * 4 - new_count * 4);
        } else {
            double p = ((double) (rnd() % (int) num)) / num;
            double cur = old_count / new_count * T;
            if (p <= cur) {
                total_count = total_count - (old_count * 4 - new_count * 4);
            } else {
                t[y1][x1] = old_val;
            }
        }
        T *= 0.90;
    }
    return false;

}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, c;
    cin >> n >> m >> c;
    while (!annealing(n, m, c)) {}
}
