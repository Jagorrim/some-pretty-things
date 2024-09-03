// Задача - В конце занятия n студентов попросили у Кирилла задачи, которых у него всего m. Каждый ученик хотел бы получить ai задач, и если он получит меньше, а именно bi , то будет зол на (ai −bi)^2 злости. Каждую задачу можно дать не более чем одному ученику. Кирилл очень не хотел бы злить своих любимых студентов, поэтому просит вас помочь минимизировать суммарную злость в классе.

#include <bits/stdc++.h>
#include <iostream>

using namespace std;


unsigned long long const mod = pow(2, 64);

struct Guy {
    unsigned long long need;
    unsigned long long got;
    unsigned long long malice;

    explicit Guy(unsigned long long const need) {
        this->need = need;
        this->got = 0;
        this->malice = (this->need - this->got) * (this->need - this->got) % mod;
    }

    bool operator<(const Guy &other) const {
        return this->malice < other.malice;
    }
};


void siftDown(vector<Guy> &heap, int index = 0) {
    Guy guy = heap[index];
    int nextIndex = -1;

    if (index * 2 + 1 < heap.size() && guy < heap[index * 2 + 1]) {
        nextIndex = index * 2 + 1;
    }

    if (index * 2 + 2 < heap.size() && guy < heap[index * 2 + 2] && heap[index * 2 + 1] < heap[index * 2 + 2]) {
        nextIndex = index * 2 + 2;
    }

    if (nextIndex == -1) {
        return;
    }


    swap(heap[index], heap[nextIndex]);
    siftDown(heap, nextIndex);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    int n, m;
    cin >> m >> n;
    vector<Guy> guys;
    int newItem;

    for (int i = 0; i < n; ++i) {
        cin >> newItem;
        guys.emplace_back(newItem);
    }

    make_heap(guys.begin(), guys.end());

    int satisfied = 0;
    unsigned long long malice = 0;
    for (Guy guy: guys) {
        malice = (malice + guy.malice) % mod;
    }

    unsigned long long oldMalice = 0;
    int maxTasks = 1;

    while (m > 0 && satisfied != n) {
        maxTasks = 1;
        Guy &guy = guys[0];


        if (guys.size() > 1 && ((guy.need - guy.got) - (guys[1].need - guys[1].got)) > maxTasks) {
            maxTasks = (guy.need - guy.got) - (guys[1].need - guys[1].got);
        }

        if (guys.size() > 2 && ((guy.need - guy.got) - (guys[2].need - guys[2].got)) > maxTasks) {
            maxTasks = (guy.need - guy.got) - (guys[2].need - guys[2].got);
        }

        if (maxTasks > m) {
            maxTasks = m;
        }

        if (maxTasks > (guy.need - guy.got)) {
            maxTasks = guy.need - guy.got;
        }


        oldMalice = guy.malice;
        guy.got += maxTasks;
        guy.malice = (guy.need - guy.got) * (guy.need - guy.got) % mod;


        malice -= (oldMalice - guy.malice);
        m -= maxTasks;

        if (guy.malice == 0) {
            satisfied += 1;
        }
        siftDown(guys);
    }

    if (satisfied == n) {
        cout << 0;
    } else {
        cout << (malice % mod);
    }


    return 0;
}
