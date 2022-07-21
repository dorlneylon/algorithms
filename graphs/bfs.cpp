#include <bits/stdc++.h>
using namespace std;

void bfs(vector <vector<int>> &g, int src, vector<bool> &vis) {
    if (vis[src]) return;
    queue <int> q;
    q.push(src);
    vis[src] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << "\n";
        for (int u = 0; u < g.size(); u++) {
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
    vector <vector<int>> g(n, vector<int>(n));
    vector<bool> vis(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];

    bfs(g, 0, vis);
}