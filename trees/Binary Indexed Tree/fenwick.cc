#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template <typename T, ll N = 200000> struct fenwick {
  vector<T> t;
  ll n = N;

  fenwick() : t(vector<ll>(N, 0)) {}
  explicit fenwick(vector<T> &a) : t(vector<T>(a.size(), 0)) {
    for (ll i = 1; i <= a.size(); ++i)
      add(i, a[i - 1]);
  }

  T sum(ll r) {
    T res = 0;
    for (; r > 0; r -= r & -r)
      res += t[r];
    return res;
  }

  T sum(ll l, ll r) { return sum(r) - sum(l - 1); }

  void add(ll k, T x) {
    for (; k <= n; k += k & -k)
      t[k] += x;
  }
};
