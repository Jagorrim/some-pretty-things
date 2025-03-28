#include <bits/stdc++.h>

using namespace std;

const int letters_count = 26;
int id = 0;


struct Vertex {
    char letter;
    int layer = 0;
    array<Vertex *, letters_count> next{};
    vector<int> string_ids{};
    int end_count = 0, id;
    Vertex *parent;

    Vertex(char letter, Vertex *parent) {
        this->letter = letter;
        this->parent = parent;
        this->id = ::id++;
    }

    ~Vertex() = default;

};

const int N = ((int) 1e6) + 10;
// обычные ссылки и сжатые
array<Vertex *, N> l, L;
// переходы для поиска хз
array<array<Vertex *, letters_count>, N> d;
Vertex root('!', nullptr);

struct Func {
    Vertex *l_func(Vertex *v) {
        if (l[v->id] != nullptr) { return l[v->id]; }
        Vertex *val;
        if (v->layer <= 1) {
            val = &root;
        } else {
            val = d_func(l_func(v->parent), v->letter);
        }

        return l[v->id] = val;
    }

    Vertex *d_func(Vertex *v, char c) {
        if (d[v->id][c - 'a'] != nullptr) { return d[v->id][c - 'a']; }

        Vertex *val;
        if (v->next[c - 'a'] != nullptr) {
            val = v->next[c - 'a'];
        } else if (v->layer == 0) {
            val = &root;
        } else {
            val = d_func(l_func(v), c);
        }

        return d[v->id][c - 'a'] = val;
    }

    Vertex *L_func(Vertex *v) {
        if (L[v->id] != nullptr) { return L[v->id]; }
        Vertex *val;
        if (l_func(v)->end_count > 0) {
            val = l_func(v);
        } else if (v->layer <= 1) {
            val = &root;
        } else {
            val = L_func(l_func(v));
        }

        return L[v->id] = val;
    }

};

int total_count = 0;

void add_to_bor(string &s, int string_id) {
    Vertex *cur_pose = &root;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (cur_pose->next[c - 'a'] == nullptr) {
            cur_pose->next[c - 'a'] = new Vertex(c, cur_pose);
            cur_pose->next[c - 'a']->layer = cur_pose->layer + 1;
        }
        cur_pose = (cur_pose->next[c - 'a']);
    }
    cur_pose->end_count++;
    cur_pose->string_ids.push_back(string_id);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string base, s;
    cin >> base;
    int n, string_id = 0;
    cin >> n;
    vector<string> dict(n);
    vector<vector<int>> answer(n);
    for (int i = 0; i < n; ++i) {
        cin >> s;
        add_to_bor(s, string_id++);
    }

    Func funcs;
    Vertex *cur = &root, *next;

    for (int i = 0; i < base.size(); ++i) {
        char c = base[i];
        cur = funcs.d_func(cur, c);
        if (cur->end_count > 0) {
            for (int s_id: cur->string_ids) {
                answer[s_id].push_back(i + 2 - cur->layer);
            }
        }
        next = funcs.L_func(cur);
        while (next->layer != 0) {
            for (int s_id: next->string_ids) {
                answer[s_id].push_back(i + 2 - next->layer);
            }
            next = funcs.L_func(next);
        }
    }

    for (auto &i: answer) {
        cout << i.size() << ' ';
        for (int j: i) { cout << j << ' '; }
        cout << '\n';
    }

    return 0;
}



































































//Едут в купе три девушки.
//Одна говорит:
//- Я люблю когда анеки строятся по одинаковым паттернам, это забавно.
//Вторая:
//- А я люблю истории с неожиданной развязкой.
//Третья:
//- А мне нравится рекурсия.
//Тут поезд резко тормозит, и с верхней полки падает купе с тремя девушками.


