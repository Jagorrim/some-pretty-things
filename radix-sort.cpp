#include <bits/stdc++.h>
#include <iostream>

using namespace std;


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, max_size = 0, is_started;
    cin >> n;
    vector<string> raw_nums;
    vector<vector<string>> classes(10);
    string raw_num;
    for (int i = 0; i < n; ++i) {
        cin >> raw_num;
        max_size = max((int) raw_num.size(), max_size);
        raw_nums.push_back(raw_num);
    }
    for (string &i: raw_nums) {
        raw_num = "";
        if (i.size() < max_size) {
            for (int j = 0; j < max_size - i.size(); ++j) {
                raw_num += '0';
            }
            i = raw_num + i;
        }
    }
    for (int i = max_size - 1; i > -1; --i) {
        classes = vector<vector<string>>(10);
        for (string num: raw_nums) {
            classes[num[i] - 48].push_back(num);
        }
        raw_nums.clear();
        for (vector<string> &j: classes) {
            for (string &j2: j) { raw_nums.push_back(j2); }
        }
    }
    for (string &j: raw_nums) {
        is_started = 0;
        for (char &j2: j) {
            if (j2 == '0' && is_started == 0) {
                continue;
            } else {
                is_started = 1;
                cout << j2;
            }
        }
        cout << ' ';
    }


    return 0;
}
