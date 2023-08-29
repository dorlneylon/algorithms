#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<vector<int>> g(N,vector<int>(N,0));
bool vis[N] = {0};

void bfs(int src) {
    if (vis[src]) return;
    queue <int> q;
    q.push(src);
    vis[src] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << "\n";
        for (int u = 0; u < N; u++) {
            if (g[v][u] > 0 && !vis[u]) {
                q.push(u);
                vis[u] = true;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];

    bfs(0);
}