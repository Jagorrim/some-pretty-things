

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, ai, q, mi, l, r, bi, index, lb, rb, mid, flag;
    vector<int> b;


    cin >> n;
    unordered_map<int, vector<int>> positions;
    for (int i = 0; i < n; ++i) {
        cin >> ai;

        if (positions.find(ai) == positions.end()) { positions[ai] = {}; }
        positions[ai].push_back(i);
    }


    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> l >> r >> mi;
        --l, --r;
        b.clear();
        for (int j = 0; j < mi; ++j) {
            cin >> bi;
            b.push_back(bi);
        }
        index = l;
        flag = 0;
        for (int j = 0; j < mi; ++j) {
            if (index > r || positions.find(b[j]) == positions.end() || positions[b[j]].back() < index) {
                flag = 1;
                break;
            }

            lb = 0;
            rb = positions[b[j]].size();

            while (rb - lb > 1) {
                mid = (lb + rb) / 2;
                if (positions[b[j]][mid] >= index) {
                    rb = mid;
                } else {
                    lb = mid;
                }
            }
            if (rb == positions[b[j]].size()) {
                --rb;
            }
            if (positions[b[j]][0] >= index){
                index += (positions[b[j]][0] - index);
            }
            else {
                index += (positions[b[j]][rb] - index);
            }
        }
        if (flag || index > r) {
            cout << "NO" << '\n';
        } else {
            cout << "YES" << '\n';
        }
    }

    return 0;
}
