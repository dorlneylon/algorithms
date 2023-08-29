#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n, h, q, tt, lx, rx;
int t[2*N], d[N];

void apply(int p, int val, int k) {
    t[p] += val*k;
    if (p < n) d[p] += val;
}

void push(int p) {
    for (int s = h; s > 0; --s) {
        int i = p >> s, k = 1 << (s - 1);
        if (d[i] != 0) {
            apply(i<<1, d[i], k);
            apply(i<<1|1, d[i], k);
            d[i] = 0;
        }
    }
}

void build() {
    for (int p = n - 1; p > 0; --p) t[p] = t[p<<1] + t[p<<1|1];
}

void build(int p) {
    for (int k = 2; p > 1; k<<=1, p>>=1) t[p>>1] = t[p] + t[p^1] + d[p>>1]*k;
}

void modify(int l, int r, int val) {
    l += n, r += n;
    int l0 = l, r0 = r;
    for (int k = 1; l < r; l>>=1, r>>=1, k<<=1) {
        if (l&1) apply(l++, val, k);
        if (r&1) apply(--r, val, k);
    }
    build(l0), build(r0-1);
}

int query(int l, int r) {
    l += n, r += n;
    int res = 0;
    push(l), push(r-1);
    for (; l < r; l>>=1, r>>=1) {
        if (l&1) res += t[l++];
        if (r&1) res += t[--r];
    }
    return res;
}

void change(int p, int val) {
    for (t[p+=n] = val; p > 1; p>>=1) t[p>>1] = t[p] + t[p^1];
}

int main() {
    cin >> n;
    h = __lg(n);
    for (int i = 0; i < n; ++i) cin >> t[n + i];
    build();
    cin >> q;

    while (q --> 0) {
        cin >> tt >> lx >> rx;
        if (tt == 1) {
            int temp;
            cin >> temp;
            modify(lx, rx+1, temp);
        } else if (tt == 2) {
            change(lx, rx);
        } else {
            cout << query(lx, rx+1) << "\n";
        }
    }
}