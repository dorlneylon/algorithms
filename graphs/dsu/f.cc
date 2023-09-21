// tinkoff start F task, O(nlogn) total complexity
#include <bits/stdc++.h>
using namespace std;

typedef uint32_t u32;
typedef int32_t i32;
const u32 maxn = 10;

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
  for (u32 i = 1; i < maxn; ++i) {
    cerr << ", ";
    __print(x[i]);
  }
  cerr << " ]";
}

void debug_out() { cerr << endl; }

template <typename H, typename... T> void debug_out(H h, T... t) {
  cerr << " ";
  __print(h);
  debug_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

u32 p[maxn], s[maxn], cnt[maxn];
vector<u32> ch[maxn];

u32 leader(u32 v) { return (p[v] == v) ? v : leader(p[v]); }

void push(u32 v) {
  for (u32 u : ch[v])
    cnt[u]++, push(u);
}

void unite(u32 a, u32 b) {
  debug(a, b, leader(a), leader(b));
  a = leader(a), b = leader(b);
  if (s[a] > s[b])
    std::swap(a, b);
  s[b] += s[a];
  p[a] = b;
  cnt[b]++;
  ch[b].push_back(a);
  debug(ch);
  push(b);
}

void init(u32 n) {
  for (u32 i = 1; i <= n; i++)
    p[i] = i, s[i] = cnt[i] = 1;
}

int main() {
  u32 n, m;
  scanf("%d%d", &n, &m);
  init(n);

  for (u32 i = 0; i < m; ++i) {
    u32 t, u, v;
    scanf("%d%d", &t, &u);
    debug(p, s, cnt);
    switch (t) {
    case 1:
      scanf("%d", &v);
      unite(u, v);
      break;
    case 2:
      scanf("%d", &v);
      if (leader(u) == leader(v))
        printf("YES\n");
      else
        printf("NO\n");
      break;
    case 3:
      printf("%d\n", cnt[u]);
    }
  }

  return 0;
}
