#ifndef __DECOMPOSITION_H
#define __DECOMPOSITION_H
#include <bits/stdc++.h>
using namespace std;

template <typename T> void __print(T x) { cerr << x; }

template <typename T> void __print(pair<T *, int> x) {
  cerr << "[ ";
  __print(x.first[0]);
  for (int i = 1; i < x.second; ++i)
    cerr << ", ", __print(x.first[i]);
  cerr << " ]";
}

void debug_out() { cerr << endl; }

template <typename H, typename... T> void debug_out(H h, T... t) {
  cerr << " ";
  __print(h);
  debug_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

const int maxn = 10, c = 4;

void solve();

int main() {
  int t;
  cin.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    solve();
  }
}

#endif
