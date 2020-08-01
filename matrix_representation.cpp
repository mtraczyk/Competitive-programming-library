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

struct matrix {
    ll **tab;
    ll numberOfRows;
    ll numberOfColumns;

    matrix(int n, int m) {
        numberOfRows = n;
        numberOfColumns = m;
        tab = new ll *[n];
        for (int i = 0; i < n; i++) {
            tab[i] = new ll[m];
            for (int j = 0; j < m; j++) {
                tab[i][j] = 0;
            }
        }
    }

    void deleteMatrix() {
        for (int i = 0; i < numberOfRows; i++) {
            delete[] tab[i];
        }
        delete[] tab;
    }

    void identityMatrix() {
        for (int i = numberOfRows - 1; i >= 0; i--) {
            tab[i][numberOfRows - 1 - i] = 1LL;
        }
    }

    void printMatrix() {
        for (int i = numberOfRows - 1; i >= 0; i--) {
            for (int j = 0; j < numberOfColumns; j++) {
                printf("%lld ", tab[i][j]);
            }
            printf("\n");
        }
    }
};

// If you want it to work for non square matrices, you have to allocate a required memory.
inline matrix operator*(const matrix &a, const matrix &b) {
    matrix c = matrix(a.numberOfRows, b.numberOfColumns);

    for (int i = 0; i < c.numberOfRows; i++) {
        for (int j = 0; j < c.numberOfColumns; j++) {
            for (int k = 0; k < a.numberOfColumns; k++) {
                c.tab[i][j] += a.tab[i][k] * b.tab[b.numberOfRows - 1 - k][j];
            }
        }
    }

    return c;
}

int main() {
    return 0;
}