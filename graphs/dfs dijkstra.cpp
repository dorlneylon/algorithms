#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<vector<int>> g(N, vector<int>(N,0));
bool vis[N] = {0};

void dfs(int src) {
    if (vis[src]) return;
    vis[src] = true;

    cout << src << "\n";

    for (int i = 0; i < N; i++)
        if (g[src][i] > 0) dfs(i);
}

void dijkstra(int src, vector<int>& d) {
    priority_queue<pair<int, int>> q;
    q.push({0, src});
    d[src] = 0;
    while (!q.empty()) {
        int p = -q.top().first;
        int v = q.top().second;
        q.pop();
        if (p > d[v]) continue;
        for (int i = 0; i < N; i++) {
            if (d[i] > d[v]+g[v][i] && g[v][i] >= 0)
                d[i] = d[v]+g[v][i],
                        q.push({-d[i], i});
        }
    }
}

int main() {
    int n, src, dest;
    cin >> n >> src >> dest;
    src--; dest--;
    vector <int> d(n,N+5);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];
    dijkstra(src, d);
    cout << d[dest];
    cout << "\n";
    dfs(src);
}