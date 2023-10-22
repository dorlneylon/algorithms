#include <bits/stdc++.h>
#define fr first
#define sc second
#define pb push_back
using namespace std;

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
template <typename K, typename V> void __print(unordered_map<K, V> &m) {
  cerr << "[ ";
  for (auto [k, v] : m) {
    if (k != m.begin()->first)
      cerr << ", ";
    cerr << "{ ";
    __print(k);
    cerr << ": ";
    __print(v);
    cerr << " }";
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

typedef long long ll;

void solve() {
  unordered_map<ll, ll> m;
  for (int i = 0; i < 10; ++i)
    m[i] = rand();
  debug(m);
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin >> t;

  while (t--)
    solve();
}
