#ifndef __EDMONDS_H
#define __EDMONDS_H
#include <bits/stdc++.h>
using namespace std;

const int maxn = 6, INF = 1e9;

template <typename T> void __print(T x) { cerr << x; }
template <typename T, typename V> void __print(pair<T, V> x) {
  cerr << "{";
  __print(x.first);
  cerr << ", ";
  __print(x.second);
  cerr << "}";
}
template <typename T> void __print(vector<T> x) {
  cerr << "[ ";
  for (auto it = x.begin(); it != x.end(); ++it) {
    if (it != x.begin())
      cerr << ", ";
    __print(*it);
  }
  cerr << " ]";
}
template <typename T> void __print(queue<T> q) {
  cerr << "[ ";
  while (!q.empty()) {
    __print(q.front());
    q.pop();
    if (!q.empty())
      cerr << ", ";
  }
  cerr << " ]";
}

template <typename T> void __print(T *x) {
  cerr << "[ ";
  for (int i = 0; i < maxn; ++i) {
    if (i)
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

void solve();

int main() {
  int t = 1;
  cin.tie(0);
  ios::sync_with_stdio(0);

  // cin >> t;

  while (t--) {
    solve();
  }
}

#endif
