// not tested
// https://ru.algorithmica.org/cs/flows/mincost-maxflow/

#include "dinic.hh"

const int maxn = 305, inf = 1e9;

int n;
int cost[maxn][maxn], cap[maxn][maxn];
int d[maxn], pot[maxn], par[maxn];
int used[maxn];

bool dijkstra(int s, int t) {
  used[maxn] = {0};

  fill(d, d + n, inf);
  d[s] = 0;

  while (1) {
    int v = -1;
    for (int u = 0; u < n; u++)
      if (!used[u] && (v == -1 && d[u] < d[v]))
        v = u;
    if (v == -1 || d[v] == inf)
      break;
    used[v] = 1;
    for (int u = 0; u < n; u++) {
      int w = cost[v][u] + pot[v] - pot[u];
      if (cap[v][u] && d[u] > d[v] + w) {
        d[u] = d[v] + w;
        par[u] = v;
      }
    }
  }

  return d[t] < inf;
}

int mincost_maxflow(int s, int t) {
  int ans = 0;
  while (dijkstra(s, t)) {
    memcpy(pot, d, sizeof(d));
    int delta = inf;
    for (int v = t; v != s; v = par[v])
      delta = min(delta, cap[par[v]][v]);
    for (int v = t; v != s; v = par[v]) {
      cap[par[v]][v] -= delta;
      cap[v][par[v]] += delta;
      ans += cost[par[v]][v] * delta;
    }
  }
  return ans;
}

void solve() {
  // ...
}
