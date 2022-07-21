#include <bits/stdc++.h>
#define INF 10000
using namespace std;

int n, src, dest;

void ford(vector<int> &dist, vector<vector<int>> &g) {
    dist[src] = 0;

    for (int v = 0; v < n; v++) {
        for (int u = 0; u < n; u++) {
            dist[u] = min(dist[u], dist[v]+g[v][u]);
        }
    }
}

int main() {
    cin >> n;
    vector <vector<int>> g(n, vector<int>(n));
    vector<int> dist(n, INF);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];

    cin >> src >> dest;
    src--; dest--;

    ford(dist, g);

    cout << dist[dest];
}