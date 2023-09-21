#include <bits/stdc++.h>

const int maxn = 1e5 + 10;

int p[maxn], s[maxn];

int leader(int v) {
    return (p[v] == v) ? v : p[v] = leader(p[v]);
}

void unite(int a, int b) {
    a = leader(a), b = leader(b);
    if (s[a] > s[b])
        std::swap(a, b);
    s[b] += s[a];
    p[a] = b;
}

void init(int n) {
    for (int i = 0; i < n; i++)
        p[i] = i, s[i] = 1;
}