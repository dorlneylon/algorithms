#include <bits/stdc++.h>
using namespace std;

const int N = 1e5; // array size limit
int n, h, q, tt, l, r;
int t[2*N], d[N];

void calc(int p) {
    if (d[p] == 0) t[p] = t[p<<1] + t[p<<1|1];
    else t[p] += d[p];
}

void apply(int p, int value) {
    t[p] += value;
    if (p < n) d[p] += value;
}

void build(int l, int r) {
    for (l += n, r += n-1; l > 1;) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) calc(i);
    }
}

void push(int l, int r) {
    int s = h;
    for (l += n, r += n-1; s > 0; --s)
        for (int i = l >> s; i <= r >> s; ++i)
            if (d[i] != 0) {
                apply(i<<1, d[i]);
                apply(i<<1|1, d[i]);
                d[i] = 0;
            }
}

void modify(int l, int r, int value) {
    if (value == 0) return;
    push(l, l + 1);
    push(r - 1, r);
    int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
        if (l&1) apply(l++, value);
        if (r&1) apply(--r, value);
    }
    build(l0, l0 + 1);
    build(r0 - 1, r0);
}

int query(int l, int r) {
    push(l, l + 1);
    push(r - 1, r);
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res += t[l++];
        if (r&1) res += t[--r];
    }
    return res;
}

int main() {
    cin >> n;
    h = __lg(n);
    for (int i = 0; i < n; ++i) cin >> t[n + i];
    cin >> q;
    while (q --> 0) {
        cin >> tt >> l >> r;
        if (tt == 1) {
            int val;
            cin >> val;
            modify(l, r, val);
            push(l, r);
        }
        build(l, r);
        cout << query(l, r) << "\n";
    }
}