// https://www.spoj.com/problems/FASTFLOW/
// all tests passed except for the master judge (TL)
// scaling won't help
#include "edmonds.hh"

template <typename T = int, const int maxn = 300, const int INF = (int)1e9>
struct edmonds {

  struct edge {
    int to, rev;
    T cap, flow;
    edge(int to, int rev = -1, T cap = T())
        : to(to), rev(rev), cap(cap), flow(T()) {}
  };

  vector<edge> adj[maxn];
  int s, t;
  bool scaling;        // O(nm^2) to O(nmlogC) with constant
  T scalingFactor = 1; // might need to be changed to eps for doubles
  int p[maxn];         // parent

  edmonds(int s = maxn - 2, int t = maxn - 1, bool scaling = false)
      : s(s), t(t), scaling(scaling) {}

  void addEdge(int u, int v, int w, bool directed = false) {
    adj[u].emplace_back(v, adj[v].size(), w);
    adj[v].emplace_back(u, adj[u].size() - 1, directed ? 0 : w);
  }

  bool bfs() {
    for (int i = 0; i < maxn; ++i)
      p[i] = -1;
    p[s] = s;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto &e : adj[u]) {
        if (p[e.to] == -1 &&
            (!scaling ? e.cap > e.flow : e.cap - e.flow >= scalingFactor)) {
          p[e.to] = u;
          if (e.to == t)
            return true;
          q.push(e.to);
        }
      }
    }

    return false;
  }

  T edmondsKarp() {
    T flow = T();

    for (scalingFactor = scaling ? 1 << 30 : 1; scalingFactor > 0;
         scalingFactor >>= 1) {
      while (bfs()) {
        T pushed = INF;
        for (int u = t; u != s; u = p[u]) {
          auto &e = adj[p[u]][adj[u][p[u]].rev]; // reverse edge
          pushed = min(pushed, e.cap - e.flow);
        }
        for (int u = t; u != s; u = p[u]) {
          auto &e = adj[p[u]][adj[u][p[u]].rev];
          e.flow += pushed;
          adj[u][e.rev].flow -= pushed;
        }
        flow += pushed;
      }
    }

    return flow;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  edmonds<long long, 5005, (long long)1e9> ed(0, n - 1, false);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    ed.addEdge(u - 1, v - 1, w);
  }
  cout << ed.edmondsKarp() << "\n";
}
