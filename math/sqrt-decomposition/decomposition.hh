#ifndef __DECOMPOSITION_H
#define __DECOMPOSITION_H
#include <bits/stdc++.h>
using namespace std;

template <typename T> void __print(T x) { cerr << x; }

template <typename T> void __print(T *x, int sz) {
  cerr << "[ " << __print(x[0]);
  for (int i = 1; i < sz; ++i)
    cerr << ", ", __print(x[i]);
  cerr << " ]";
}

const int maxn = 1e5, c = 330;

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
