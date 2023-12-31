#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template<typename T = ll, ll N = 20000>
struct segtree {
  ll n, h;
  T t[2*N], d[N];
  T (*f)(T, T) = [](T a, T b) { return a + b; };

  segtree(): n(N), h(__lg(N)) {}
  segtree(T (*f)(T, T), ll _N = N): n(_N), h(__lg(_N)), f(f) {}

  explicit segtree(vector<T> &a, T (*f)(T, T)): n(a.size()), h(__lg(a.size())), f(f) {
    for (ll i = 0; i < n; ++i)
      t[n+i] = a[i];
    build();
  }

  explicit segtree(vector<T> &a): n(a.size()), h(__lg(a.size())) {
    for (ll i = 0; i < n; ++i)
      t[n+i] = a[i];
    build();
  }

  explicit segtree(ll _n): n(_n), h(__lg(_n)) {}

  /* TODO: rewrite depending on f */
  void apply(ll p, T val, ll k) {
      t[p] += val*k;
      if (p < n) d[p] += val;
  }

  void push(ll p) {
    for (ll s = h; s > 0; --s) {
      ll i = p >> s, k = 1 << (s - 1);
      if (d[i] != 0) {
        apply(i<<1, d[i], k);
        apply(i<<1|1, d[i], k);
        d[i] = 0;
      }
    }
  }

  void build() {
    for (ll p = n - 1; p > 0; --p)
      t[p] = f(t[p<<1], t[p<<1|1]);
  }

  void build(ll p) {
      for (ll k = 2; p > 1; k<<=1, p>>=1)
        t[p>>1] = f(t[p], t[p^1]) + d[p>>1]*k;
  }

  void modify(ll l, ll r, T val) {
      l += n, r += n;
      ll l0 = l, r0 = r;
      for (ll k = 1; l < r; l>>=1, r>>=1, k<<=1) {
          if (l&1)
            apply(l++, val, k);
          if (r&1)
            apply(--r, val, k);
      }
      build(l0), build(r0-1);
  }

  T query(ll l, ll r) {
    l += n, r += n;
    T resl = T(), resr = T();
    push(l), push(r-1);
    for (; l < r; l>>=1, r>>=1) {
      if (l&1)
        resl = f(resl, t[l++]);
      if (r&1)
        resr = f(resr, t[--r]);
    }
    return f(resl, resr);
  }

  void change(ll p, T val) {
    for (t[p+=n] = val; p > 1; p>>=1)
      t[p>>1] = f(t[p], t[p^1]);
  }
};

int main() {
  ll n, q;
  cin >> n >> q;
  segtree st(n);
  for (ll i = 0; i < n; ++i) {
    cin >> st.t[n+i];
  }
  st.build();

  while (q--) {
    char t;
    cin >> t;
    if (t == '+') {
      ll l, r, val;
      cin >> l >> r >> val;
      --l, --r;
      st.modify(l, r+1, val);
    } else {
      ll l, r;
      cin >> l >> r;
      --l, --r;
      cout << st.query(l, r+1) << "\n";
    }
  }
}
