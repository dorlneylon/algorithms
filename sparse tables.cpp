#include <bits/stdc++.h>
using namespace std;

int n, logn;

void build(int** st) {
    for (int l = 0; l < logn - 1; l++)
        for (int r = 0; r + (2 << l) <= n; r++)
            st[l+1][r] = min(st[l][r], st[l][r + (1 << l)]); // 1 << l -- сдвиг на l битов влево -- 2^l.
}

int rmq(int **st, int l, int r) {
    int t = __lg(r - l);
    return min(st[t][l], st[t][r - (1 << t)]);
}

int main() {
    cin >> n;
    logn = __lg(n); // подсчет округленного логарифма за O(1)

    int a[n];
    for (int i = 0; i < n; i++) cin >> a[i];

    int** st = new int*[logn];
    for (int i = 0; i < logn; i++)
        st[i] = new int[n];

    memcpy(st[0], a, sizeof a); // копируем массив a в st

    build(st);

    int t, l, r;
    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> l >> r;
        cout << rmq(st, l, r) << "\n";
    }

    for (int i = 0; i < logn; i++)
        delete[] st[i];
    delete[] st;
}