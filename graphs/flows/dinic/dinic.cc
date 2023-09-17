#include "dinic.hh"

int n, m, u[10005], v[10005], c[10005], a[10005], b[10005], du[10005],
    in[20005], s, t, ss, tt;

struct edge {
  int son, val, next;
} edge[500005];

int head[20005], cnt = 1, nowb[20005], dep[20005], maxflow;

void adde(int x, int y, int z) {
  edge[++cnt] = {y, z, head[x]};
  head[x] = cnt;
  edge[++cnt] = {x, 0, head[y]};
  head[y] = cnt;
}

queue<int> Q;

// https://e-maxx.ru/algo/dinic

bool bfs() {
  memset(dep, 127, sizeof(dep));
  dep[ss] = 0;
  Q.push(ss);
  while (!Q.empty()) {
    int nr = Q.front();
    Q.pop();
    for (int i = head[nr]; i > 0; i = edge[i].next) {
      if (edge[i].val && dep[nr] + 1 < dep[edge[i].son]) {
        dep[edge[i].son] = dep[nr] + 1;
        Q.push(edge[i].son);
      }
    }
  }
  return dep[tt] < 1000000000;
}

int dfs(int x, int nfl) {
  if (x == tt)
    return nfl;
  int nuse = 0;
  for (int i = nowb[x]; i > 0; i = edge[i].next) {
    nowb[x] = i;
    if (edge[i].val && dep[x] + 1 == dep[edge[i].son]) {
      int flw = dfs(edge[i].son, min(edge[i].val, nfl - nuse));
      edge[i].val -= flw;
      edge[i ^ 1].val += flw;
      nuse += flw;
      if (nuse == nfl)
        break;
    }
  }
  return nuse;
}

void dinic() {
  while (bfs()) {
    memcpy(nowb, head, sizeof(nowb));
    maxflow += dfs(ss, 1000000000);
  }
}

void solve() {
  cin >> n >> m;
  s = 0;
  t = n + m + 1;
  ss = n + m + 2;
  tt = n + m + 3;

  for (int i = 1; i <= n; i++)
    cin >> c[i];

  for (int i = 1; i <= n; i++)
    cin >> a[i];

  for (int i = 1; i <= m; i++)
    cin >> u[i] >> v[i], du[u[i]]++, du[v[i]]++;

  for (int i = 1; i <= n; i++) {
    if (!c[i])
      continue;

    if ((du[i] + a[i]) & 1) {
      cout << "NO" << endl;
      return;
    }

    b[i] = (du[i] + a[i]) / 2;
  }

  for (int i = 1; i <= m; i++) {
    in[n + i]++;
    in[s]--;
    adde(n + i, u[i], 1);
    adde(n + i, v[i], 1);
  }

  for (int i = 1; i <= n; i++) {
    if (c[i] == 0)
      adde(i, t, INF);
    else
      in[i] -= b[i], in[t] += b[i];
  }

  for (int i = s; i <= t; i++) {
    if (in[i] > 0)
      adde(ss, i, in[i]);
    else
      adde(i, tt, -in[i]);
  }

  adde(t, s, 1000000000);
  dinic();
  for (int i = head[ss]; i > 0; i = edge[i].next) {
    if (edge[i].val) {
      cout << "NO" << endl;
      return;
    }
  }

  for (int i = n + 1; i <= n + m; i++) {
    for (int j = head[i]; j > 0; j = edge[j].next) {
      if (!edge[j].val && edge[j].son >= 1 && edge[j].son <= n) {
        if (edge[j].son == u[i - n])
          swap(u[i - n], v[i - n]);
      }
    }
  }
  cout << "YES" << endl;
  for (int i = 1; i <= m; i++)
    cout << u[i] << " " << v[i] << endl;
}
