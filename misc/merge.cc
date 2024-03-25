#include <bits/stdc++.h>
#ifdef ONPC
#include "algo/debug.h"
#else
#define debug(...) 42
#endif
#define fr first
#define sc second
#define pb push_back
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void merge(ll *a, ll l, ll r) {
  for (ll gap = (l + r) >> 1; gap > 0; gap >>= 1)
    for (ll i = 0; l + gap + i < r; ++i)
      if (a[l + i] > a[l + gap + i])
        swap(a[l + i], a[l + gap + i]);
}

// O(n(logn)^2) time complexity
// O(1)         extra space
void merge_sort(ll *a, ll l, ll r) {
  if (l < r - 1) {
    ll m = (l + r) >> 1;

    merge_sort(a, l, m);
    merge_sort(a, m, r);

    merge(a, l, r);
  }
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(0);

  ll n;
  cin >> n;
  ll a[n];

  for (ll i = 0; i < n; ++i)
    cin >> a[i];

  merge_sort(a, 0, n);

  for (ll i = 0; i < n; ++i)
    cout << a[i] << " ";
}
