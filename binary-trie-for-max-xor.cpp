#include <iostream>
#include <vector>

using namespace std;


struct Node {
    int c0, c1, count;

    Node(int c0, int c1, int count) {
        this->c0 = c0, this->c1 = c1, this->count = count;
    }

    Node() {}
};

int depth = 32; // максимально допустимое кол-во битов, => максимальный бит = 2^(depth - 1)

int pow2(int power) {
    if (power == 0) { return 1; }
    else { return 2 << (power - 1); }
}

vector<Node> trie{{-1, -1, 0}};

void add(int num) {
    int pos = 0;
    for (int i = depth - 1; i >= 0; --i) {
        if ((pow2(i) & num) != 0) {
            if (trie[pos].c1 == -1) {
                trie[pos].c1 = trie.size();
                trie.emplace_back(-1, -1, 0);
                pos = trie.size() - 1;
            } else {
                pos = trie[pos].c1;
            }
        } else {
            if (trie[pos].c0 == -1) {
                trie[pos].c0 = trie.size();
                trie.emplace_back(-1, -1, 0);
                pos = trie.size() - 1;
            } else {
                pos = trie[pos].c0;
            }
        }
        ++trie[pos].count;
    }
}

void erase(int num) {
    int pos = 0;
    for (int i = depth - 1; i >= 0; --i) {
        if ((pow2(i) & num) != 0) {
            pos = trie[pos].c1;
        } else {
            pos = trie[pos].c0;
        }
        --trie[pos].count;
    }
}


int solve(int num) {
    int pos = 0, answer = 0;
    for (int i = depth - 1; i >= 0; --i) {
        if ((pow2(i) & num) != 0) {
            if (trie[pos].c0 != -1 && trie[trie[pos].c0].count > 0) {
                pos = trie[pos].c0;
                answer += pow2(i);
            } else if (trie[pos].c1 != -1 && trie[trie[pos].c1].count > 0) {
                pos = trie[pos].c1;
            } else { return num; }
        } else {
            if (trie[pos].c1 != -1 && trie[trie[pos].c1].count > 0) {
                pos = trie[pos].c1;
                answer += pow2(i);
            } else if (trie[pos].c0 != -1 && trie[trie[pos].c0].count > 0) {
                pos = trie[pos].c0;
            } else { return num; }
        }
    }
    return max(answer, num);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int q, x;
    cin >> q;
    char o;
    while (q--) {
        cin >> o >> x;
        if (o == '+') {
            add(x);
        } else if (o == '-') {
            erase(x);
        } else {
            cout << solve(x) << '\n';
        }
    }

}
