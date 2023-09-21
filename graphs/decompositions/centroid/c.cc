// https://codeforces.com/contest/321/problem/C
#include <bits/stdc++.h>
using namespace std;

typedef uint32_t u32;
typedef int32_t i32;
const u32 maxn = 1e5 + 5;

template <typename T> void __print(T x) { cerr << x; }
template <typename T> void __print(vector<T> x) {
  cerr << "[ ";
  for (auto it = x.begin(); it != x.end(); ++it) {
    if (it != x.begin())
      cerr << ", ";
    __print(*it);
  }
  cerr << " ]";
}
template <typename T> void __print(T *x) {
  cerr << "[ ";
  __print(*x);
  for (u32 i = 1; i < maxn; ++i)
    cerr << ", " << x[i];
  cerr << " ]";
}

void debug_out() { cerr << endl; }

template <typename H, typename... T> void debug_out(H h, T... t) {
  cerr << " ";
  __print(h);
  debug_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

bool used[maxn];
u32 sz[maxn];
vector<u32> g[maxn];
char d[maxn];

void sizes(u32 u, u32 p) {
  sz[u] = 1;
  for (u32 v : g[u])
    if (v != p && !used[v])
      sizes(v, u), sz[u] += sz[v];
}

u32 centroid(u32 u, u32 p, u32 n) {
  for (u32 v : g[u])
    if (v != p && sz[v] > n / 2 && !used[v])
      return centroid(v, u, n);
  return u;
}

void solve(u32 v, char rk) {
  if (rk > 'Z')
    printf("Impossible!"), exit(0);
  d[v] = rk;
  used[v] = true;
  for (u32 u : g[v])
    if (!used[u])
      sizes(u, v), solve(centroid(u, v, sz[u]), rk + 1);
}

int main() {
  u32 n;
  scanf("%" SCNu32, &n);
  for (u32 i = 0; i < n - 1; ++i) {
    u32 u, v;
    scanf("%" SCNu32 "%" SCNu32, &u, &v);
    g[u].push_back(v), g[v].push_back(u);
  }

  sizes(1, 0);
  u32 cent = centroid(1, 0, sz[1]);
  solve(cent, 'A');

  for (u32 i = 1; i <= n; ++i)
    printf("%c ", d[i]);
}
