//Author : Michał Traczyk
// Remember to shuffle the edges if needed.

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int M = 1000007;
const ll q = 7057594037927903;
const ll prime = 2137;
#define pb push_back
#define mp make_pair
#define f first
#define s second

int match[M], n; //n - number of vertices
bool visited[M], color[M];
vector<int> v[M];

int dfs(int h) {
    if (visited[h]) {
        return 0;
    }
    visited[h] = true;

    for (int i = 0; i < (int) v[h].size(); i++) {
        if (!match[v[h][i]]) {
            match[h] = v[h][i];
            match[v[h][i]] = h;
            return 1;
        } else if (dfs(match[v[h][i]])) {
            match[h] = v[h][i];
            match[v[h][i]] = h;
            return 1;
        }
    }
    return 0;
}

void find_maximal_matching() {
    int res = 0, pres = -1;
    while (res != pres) {
        pres = res;
        for (int i = 1; i <= n; i++) {
            visited[i] = 0;
        }

        for (int i = 1; i <= n; i++)
            if (!match[i] && !color[i]) {
                res += dfs(i);
            }
    }
}

void color_the_graph(int h) {
    visited[h] = 1;
    for (int i = 0; i < (int) v[h].size(); i++)
        if (!visited[v[h][i]]) {
            if (color[h] == 0) {
                color[v[h][i]] = 1;
            } else {
                color[v[h][i]] = 0;
            }
            color_the_graph(v[h][i]);
        }
}

void find_coloring() {
    for (int i = 1; i <= n; i++)
        if (!visited[i]) {
            color_the_graph(i);
        }
}

int main() {
    find_coloring();
    find_maximal_matching();

    return 0;
}


