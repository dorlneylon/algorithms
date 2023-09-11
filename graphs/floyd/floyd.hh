#ifndef FLOYD_H
#define FLOYD_H
#include <bits/stdc++.h>
using namespace std;

typedef __uint32_t u32;
typedef __int32_t  i32;
const u32 INF = -1;
const u32 N = 1e3;
u32 n, m;

vector<vector<u32>> d(N, vector<u32>(N, INF));

void floyd();

int main() {
    cin >> n >> m;
    
    while (m--) {
        u32 u, v, w;
        cin >> u >> v >> w;
        d[u][v] = d[v][u] = w;
    }

    for (u32 i = 0; i < n; ++i)
        d[i][i] = 0;

    floyd();

    for (u32 i = 0; i < n; ++i)
        for (u32 j = 0; j < n; ++j)
            cout << D[i*n + j] << " \n"[j==n-1];
}

#endif