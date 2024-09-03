// Задача - Дан ориентированный взвешенный граф. Найдите кратчайшее расстояние от одной заданной вершины до другой. В первой строке содержатся три числа: N, S и F (1≤ N≤ 100, 1≤ S, F≤ N), где N – количество вершин графа, S – начальная вершина, а F – конечная. В следующих N строках вводится по N чисел, не превосходящих 100, – матрица смежности графа, где -1 означает отсутствие ребра между вершинами, а любое неотрицательное число – присутствие ребра данного веса. На главной диагонали матрицы записаны нули.
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct Way {
    int from;
    int to;
    int cost;
    int totalCost;

    bool operator<(const Way &other) const {
        return this->totalCost >= other.totalCost;
    }
};


int dijkstra() {
    int n, m;
    cin >> n >> m;

    vector<int> saw(n, 0);
    map<int, vector<Way> > graph;
    for (int i = 0; i < n; i++) {
        graph[i] = {};
    }


    priority_queue<Way> cur;
    vector<int> done(n, -1);

    int from, to, cost;
    Way way;
    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> cost;

        way = {from, to, cost, cost};
        graph[from].push_back(way);

        way = {to, from, cost, cost};
        graph[to].push_back(way);
    }
    int start;
    cin >> start;

    for (Way i: graph[start]) {
        cur.push(i);
    }
    done[start] = 0;
    saw[start] = 1;

    while (true) {
        if (cur.empty()) {
            break;
        }
        way = cur.top();
        cur.pop();

        if (saw[way.to] == 1) {
            continue;
        }
        done[way.to] = done[way.from] + way.cost;
        saw[way.to] = 1;

        for (Way newWay: graph[way.to]) {
            if (saw[newWay.to] == 1) {
                continue;
            }
            newWay.totalCost += way.totalCost;
            cur.push(newWay);
        }
    }

    int item;
    for (int i = 0; i < n; ++i) {
        item = done[i];
        if (item == -1) {
            cout << 2009000999;
        } else {
            cout << item;
        }

        if (i != (n - 1)) {
            cout << ' ';
        } else {
            cout << '\n';
        }
    }
    return 0;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int num;
    cin >> num;
    for (int i = 0; i < num; ++i) {
        dijkstra();
    }


    return 0;
}
