#include <bits/stdc++.h>
#include <iostream>

// task (H) - https://algocode.ru/files/course_sbory2024_municip/contest-46159-ru_1.pdf 

struct Node {
    int has;
    long long total_count;
    long long start;
    long long end;

    Node(int has,
         long long total_count,
         long long start,
         long long end) {
        this->has = has;
        this->total_count = total_count;
        this->start = start;
        this->end = end;

    }

};


using namespace std;

pair<vector<Node>, long long> create_segment_tree(long long n) {
    pair<vector<Node>, long long> res;


    int i = 0;
    long long cur_size, index = 0, end;
    end = pow(2, ceil(log2(n)));

    while (true) {
        cur_size = pow(2, i);
        for (int j = 0; j < cur_size; ++j) {
            if (i == 0) {
                res.first.emplace_back(0, 0, 1, end);
            } else {
                if ((res.second + j) % 2 == 1) {
                    res.first.emplace_back(0, 0,
                                           res.first[(index - 1) / 2].start,
                                           (res.first[(index - 1) / 2].start +
                                            res.first[(index - 1) / 2].end) / 2);
                } else {
                    res.first.emplace_back(0, 0,
                                           (res.first[(index - 1) / 2].start +
                                            res.first[(index - 1) / 2].end) / 2 + 1,
                                           res.first[(index - 2) / 2].end);
                }
            }
            index += 1;
        }
        if (cur_size >= end) {
            break;
        }
        res.second += cur_size;
        ++i;
    }
    res.second -= 1;
    return res;

}


long long get_attacks_at_range(long long start, long long end, long long cur_pos, vector<Node> &data) {
    long long sum = 0, center = (data[cur_pos].start + data[cur_pos].end) / 2;
    if (start == data[cur_pos].start && end == data[cur_pos].end) {
        return data[cur_pos].has;
    }

    if (start >= data[cur_pos].start && start <= center) {
        sum += get_attacks_at_range(start, min(center, end), cur_pos * 2 + 1, data);
    }

    if (end > center && end <= data[cur_pos].end) {
        sum += get_attacks_at_range(max(center + 1, start), end, cur_pos * 2 + 2, data);
    }

    return sum;
}

void update(long long cur_pos, long long to_plus, vector<Node> &data) {
    data[cur_pos].has += to_plus;

    if (cur_pos == 0) {
        return;
    }

    if (cur_pos % 2 == 1) {
        update((cur_pos - 1) / 2, to_plus, data);
    } else {
        update((cur_pos - 2) / 2, to_plus, data);
    }

}


signed main() {
//    ios::sync_with_stdio(0);
//    cin.tie(0);

//    ifstream cin;
//    cin.open("a.txt");
//    clock_t tStart = clock();

    long long n, q, t, x1, y1, x2, y2, attacked1, attacked2, tree_size;
    cin >> n >> q;
    pair<vector<Node>, long long> res = create_segment_tree(n);
    vector<Node> horizontal = res.first, vertical = res.first;
    tree_size = res.second;

    for (long long i = 0; i < q; ++i) {
        cin >> t;
        if (t == 1) {
            cin >> x1 >> y1;
            vertical[tree_size + x1].total_count += 1;
            if (vertical[tree_size + x1].total_count == 1) {
                update(tree_size + x1, 1, vertical);
            }

            horizontal[tree_size + y1].total_count += 1;
            if (horizontal[tree_size + y1].total_count == 1) {
                update(tree_size + y1, 1, horizontal);
            }
        } else if (t == 2) {
            cin >> x1 >> y1;
            vertical[tree_size + x1].total_count -= 1;
            if (vertical[tree_size + x1].total_count == 0) {
                update(tree_size + x1, -1, vertical);
            }

            horizontal[tree_size + y1].total_count -= 1;
            if (horizontal[tree_size + y1].total_count == 0) {
                update(tree_size + y1, -1, horizontal);
            }
        } else {
            cin >> x1 >> y1 >> x2 >> y2;

            attacked1 = get_attacks_at_range(x1, x2, 0, vertical);
            attacked2 = get_attacks_at_range(y1, y2, 0, horizontal);

            if (attacked1 == (x2 - x1 + 1) || attacked2 == (y2 - y1 + 1)) {
                cout << "Yes" << '\n';
            } else {
                cout << "No" << '\n';
            }
        }
    }
//    cout << (double) (clock() - tStart) / CLOCKS_PER_SEC;


    return 0;
}
