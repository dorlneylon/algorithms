#include <bits/stdc++.h>
#define INF 1001
using namespace std;

void dfs(vector<vector<int>>* g, vector<bool>*vis, int src) {
    if ((*vis)[src]) return;
    (*vis)[src] = true;

    cout << src << "\n";

    for (int i = 0; i < (*g).size(); i++) {
        if ((*g)[src][i] > 0) dfs(g, vis, i);
    }
}

void dijkstra(vector<vector<int>>* g, vector<int>* d, int src) {
    priority_queue<pair<int, int>> q;
    q.push({0, src});
    (*d)[src] = 0;
    while (!q.empty()) {
        int p = -q.top().first;
        int v = q.top().second;
        q.pop();
        if (p > (*d)[v]) continue;
        for (int i = 0; i < (*g).size(); i++) {
            if ((*d)[i] > (*d)[v]+(*g)[v][i] && (*g)[v][i] >= 0)
                (*d)[i] = (*d)[v]+(*g)[v][i],
                q.push({-(*d)[i], i});
        }
    }
}

int main() {
    int n, src, dest;
    cin >> n >> src >> dest;
    src--; dest--;
    vector <vector<int>> g(n, vector<int>(n));
    vector <int> d(n,INF);
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];
    dijkstra(&g, &d, src);
    cout << d[dest];
    cout << "\n";
    dfs(&g, &vis, src);
}