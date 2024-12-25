#include <bits/stdc++.h>
#include <iostream>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long n, item;
    int l, r, mid;
    cin >> n;
    vector<long long> a, answer, prev(n, -1);
    vector<pair<long long, int>> min_ends(n + 1, {10e17, -1});
    min_ends[0].first = -10e17;
    for (int i = 0; i < n; ++i) {
        cin >> item;
        a.push_back(item);
    }

    for (int i = 0; i < n; ++i) {

        l = 0;
        r = n + 2;
        while (r - l > 1) {
            mid = (l + r) / 2;
            if (a[i] <= min_ends[mid].first) {
                r = mid;
            } else {
                l = mid;
            }
        }
        min_ends[r].first = a[i];
        min_ends[r].second = i;
        prev[i] = min_ends[r - 1].second;
    }
    for (int i = n; i > -1; --i) {
        if (min_ends[i].first != 10e17 && min_ends[i].first != -10e17) {
            cout << i << '\n';
            auto cur_index = min_ends[i].second;

            while (true) {
                answer.push_back(a[cur_index]);
                if (prev[cur_index] == -1) { break; }
                cur_index = prev[cur_index];
            }
            reverse(answer.begin(), answer.end());
            for (long long j: answer) {
                cout << j << ' ';
            }
            break;
        }
    }


    return 0;
}
