// task - https://informatics.msk.ru/mod/statements/view.php?id=1975&chapterid=486#1
#include <bits/stdc++.h>


#define int long long

using namespace std;
random_device lal;
mt19937 rnd(lal());
const static int inf = 1e18;


vector<int> annealing(int n, int k) {
    double best_res, cur_res = 0, new_res, T = 1, num = 1'000'000;
    int total_sum = (1 + n) * n / 2;
    int per_sum = total_sum / k;
    vector<int> cur_state(n);
    shuffle(cur_state.begin(), cur_state.end(), rnd);
    vector<int> sums(k);
    for (int i = 0; i < n; ++i) {
        cur_state[i] = i % k;
        sums[i % k] += i + 1;
    }
    for (int i: sums) {
        if (i == per_sum) { ++cur_res; }
    }
    best_res = cur_res;
    for (int t = 0; t < 100'000; ++t) {

        if (best_res == k) { return cur_state; }

        int i = rnd() % n, j = rnd() % n;
        while (cur_state[i] == cur_state[j] && n != 1) {
            i = rnd() % n, j = rnd() % n;
        }
        new_res = cur_res;
        int count1 = (int) (sums[cur_state[i]] == per_sum) + (int) (sums[cur_state[j]] == per_sum);
        sums[cur_state[i]] -= (i + 1);
        sums[cur_state[i]] += (j + 1);
        sums[cur_state[j]] -= (j + 1);
        sums[cur_state[j]] += (i + 1);
        int count2 = (int) (sums[cur_state[i]] == per_sum) + (int) (sums[cur_state[j]] == per_sum);
        swap(cur_state[i], cur_state[j]);
        new_res += (double) (count2 - count1);
        if (new_res >= cur_res) {
            cur_res = new_res;
            best_res = max(best_res, cur_res);
        } else {
            double chance;
            if (cur_res == 0 || (new_res / cur_res) * T == 0) {
                chance = 1;
            } else { chance = (new_res / cur_res) * T; }
            double real = ((double) (rnd() % (int) num)) / num;
            if (real <= chance) {
                cur_res = new_res;
                best_res = max(best_res, cur_res);
            } else {
                swap(cur_state[i], cur_state[j]);
                sums[cur_state[i]] += (i + 1);
                sums[cur_state[i]] -= (j + 1);
                sums[cur_state[j]] += (j + 1);
                sums[cur_state[j]] -= (i + 1);
            }
        }

        T *= 0.999;
    }
    return {};
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    if (n == 1) {
        cout << 1;
        return 0;
    }
    if (((1 + n) * n / 2) % k != 0) {
        cout << 0;
        return 0;
    }

    for (int i = 0; i < 1000; ++i) {
        auto res = annealing(n, k);
        if (!res.empty()) {
            vector<vector<int>> prizes(k);
            for (int j = 0; j < n; ++j) {
                prizes[res[j]].push_back(j + 1);
            }
            for (auto &j: prizes) {
                for (int num: j) { cout << num << ' '; }
                cout << '\n';
            }
            return 0;
        }
    }
    cout << 0;

}
