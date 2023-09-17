// https://www.spoj.com/problems/FASTFLOW/
// AC .2 s with scaling 0.04 s without
#include "dinic.hh"

template <typename T = int, int maxn = 300, const long long INF = 1000000000>
struct dinic {
  struct edge {
    int v, rev;  // v - destination, rev - index of the source vertex
    T cap, flow; // cap - capacity, flow - current flow
    edge(int v = 0, int rev = 0, T cap = T(), T flow = T())
        : v(v), rev(rev), cap(cap), flow(flow) {}
  };
  bool scaling;
  int lim; // if lim is 1 then it is normal dinic. otherwise it is scaled.
           // scaling boosts O(n^2m) to O(nmlogC) where C is the capacity.
           // however, scaling provides greater constants.
  vector<edge> adj[maxn];
  int s, t;
  int cur[maxn];
  int d[maxn];

  explicit dinic(int s = maxn - 2, int t = maxn - 1, bool scaling = false)
      : s(s), t(t), scaling(scaling), lim(1) {}

  void addEdge(int a, int b, T cap, bool isDirected = false) {
    adj[a].push_back({b, adj[b].size(), cap, 0});
    adj[b].push_back({a, adj[a].size() - 1, isDirected ? 0 : cap, 0});
  }

  bool buildLevelGraph() {
    for (int i = 0; i < maxn; ++i)
      d[i] = -1; // -1 - not visited
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (d[t] == -1 && !q.empty()) {
      // debug(d, q);
      int u = q.front();
      q.pop();
      for (auto e : adj[u]) {
        if (d[e.v] == -1 && e.flow < e.cap &&
            (!scaling || e.cap - e.flow >= lim)) { // next level of level graph:
          q.push(e.v); // if v is not yet in the level graph, and uv flow
          d[e.v] =
              d[u] + 1; // is not yet 0 then add v vertex in the level graph
        }
      }
    }
    return d[t] != -1; // we have reached t
  }

  T propagate(int v,
              T flow) { // try to push flow from v to t. flow is
                        // initially equal to the flow of the path from s to v
    if (!flow || v == t)
      return flow;
    for (; cur[v] < adj[v].size(); cur[v]++) { // start from the last edge
      auto &e = adj[v][cur[v]]; // and try to push flow through it
      // debug(e, adj, d);
      if (d[e.v] != d[v] + 1)
        continue;
      T pushed = propagate(e.v, min(flow, e.cap - e.flow));
      // debug(e, pushed, adj, cur[v]);

      if (pushed) {
        e.flow += pushed;
        adj[e.v][e.rev].flow -= pushed;
        return pushed;
      }
    }
    return T();
  }

  T maxFlow() {
    T flow = T();
    for (lim = scaling ? (1 << 30) : 1; lim > 0; lim >>= 1) {
      while (buildLevelGraph()) {
        // debug(adj, flow, lim);
        for (int i = 0; i < maxn; ++i)
          cur[i] = 0; // cur[v] represents the last edge we used in the dfs
        while (T f = propagate(s, INF))
          flow += f;
      }
    }
    return flow;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  dinic<long long, 5005, (long long)1e9> d(0, n - 1);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    d.addEdge(u, v, w);
  }

  cout << d.maxFlow() << "\n";
}
