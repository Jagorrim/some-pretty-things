#include <bits/stdc++.h>
#include <iostream>

using namespace std;

mt19937 rnd(42);
vector<int> data;


void quicksort(int i, int j) {
    if (i == j) {
        return;
    } else if (j - i == 1) {
        if (::data[j] < ::data[i]) {
            swap(::data[j], ::data[i]);
        }
        return;
    }

    int base_item_index = rnd() % (j - i + 1) + i;
    vector<int> less, eq, more;

    for (int to_it = i; to_it <= j; ++to_it) {
        if (::data[to_it] < ::data[base_item_index]) {
            less.push_back(::data[to_it]);
        } else if (::data[to_it] == ::data[base_item_index]) {
            eq.push_back(::data[to_it]);
        } else {
            more.push_back(::data[to_it]);
        }
    }
    int index = 0, less_size = less.size(), eq_size = eq.size(), more_size = more.size();
    for (int to_it = i; to_it <= j; ++to_it) {
        if (index < less_size) {
            ::data[to_it] = less[index];
        } else if (index >= less_size && index < less_size + eq_size) {
            ::data[to_it] = eq[index - less_size];
        } else {
            ::data[to_it] = more[index - less_size - eq_size];
        }
        ++index;
    }
    less.clear();
    eq.clear();
    more.clear();

    if (less_size > 0) {
        quicksort(i, i + less_size - 1);
    }
    if (more_size > 0) {
        quicksort(i + less_size + eq_size, j);
    }


}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, item;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> item;
        ::data.push_back(item);
    }
    quicksort(0, n - 1);
    for (auto i: ::data) {
        cout << i << ' ';
    }


    return 0;
}
