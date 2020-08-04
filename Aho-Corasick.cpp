//Author : Michał Traczyk

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int M = 1e6 + 7;
const ll q = 7057594037927903;
const ll prime = 2137;
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define ios ios_base::sync_with_stdio(0)
#define all(x) (x).begin(), (x).end()

struct Aho {
    queue<int> Q;
    int *fail = new int[M];
    ll *occurences = new ll[M];
    int **trie = new int *[M];
    int nxt = 1;

    Aho() {
        for (int i = 0; i < M; i++) {
            trie[i] = new int[28];
        }
    }

    void addPattern(string pattern) {
        int act = 1;
        for (char c : pattern) {
            if (!trie[act][c - 'a']) {
                trie[act][c - 'a'] = ++nxt;
            }
            act = trie[act][c - 'a'];
        }
        occurences[act]++;
    }

    void failLinks() {
        Q.push(1);
        fail[1] = 1;
        while (!Q.empty()) {
            int act = Q.front();
            Q.pop();

            for (char i = 'a'; i <= 'z'; i++) {
                if (trie[act][i - 'a']) {
                    if (act == 1) {
                        fail[trie[act][i - 'a']] = 1;
                        Q.push(trie[act][i - 'a']);
                        continue;
                    }

                    int f = fail[act];
                    while (f > 1 && !trie[f][i - 'a']) {
                        f = fail[f];
                    }

                    if (trie[f][i - 'a']) {
                        f = trie[f][i - 'a'];
                    }

                    fail[trie[act][i - 'a']] = f;
                    occurences[trie[act][i - 'a']] += occurences[f];
                    Q.push(trie[act][i - 'a']);
                }
            }
        }
    }

    ll numberOfOccurences(string pattern) {
        int act = 1;
        ll res = 0LL;
        for (char c : pattern) {
            while (act > 1 && !trie[act][c - 'a']) {
                act = fail[act];
            }

            if (trie[act][c - 'a']) {
                act = trie[act][c - 'a'];
            }
            res += occurences[act];
        }
        return res;
    }

    void freeMemory(void) {
        delete[] fail;
        delete[] occurences;
        for (int i = 0; i < M; i++) {
            delete[] trie[i];
        }

        delete[] trie;
    }
};
