// TODO...

#include "centroid.hh"

vector<pair<int, int>> adj[maxn];
int s[maxn] = {0};

int sizes(int v) {
  s[v] = 1;
  for (auto [u, w] : adj[v])
    s[v] += sizes(u);
  return s[v];
}

int centroid(int v, int n) {
  for (auto [u, w] : adj[v])
    if (s[u] > n / 2)
      return centroid(u, n);
  return v;
}

void init(int n) {
  for (int i = 1; i <= n; ++i)
    s[i] = sizes(i);
}

void solve() {
  int n, l, w;
  cin >> n >> l >> w;
  for (int i = 1; i < n; ++i) {
    int p, sz;
    cin >> p >> sz;
    adj[p].push_back({i + 1, sz});
  }
  init(n);
}
