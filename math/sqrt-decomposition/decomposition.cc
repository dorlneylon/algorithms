#include "decomposition.hh"

int sum(int *a, int *b, int *add, int l, int r) {
  int res = 0;
  while (l <= r) {
    if (l % c == 0 && l + c - 1 <= r) {
      res += b[l / c];
      l += c;
    } else {
      res += a[l] + add[l / c];
      l += 1;
    }
  }
  return res;
}

void upd(int *a, int *b, int *add, int l, int r, int x) {
  while (l <= r) {
    if (l % c == 0 && l + c - 1 <= r) {
      b[l / c] += c * x;
      add[l / c] += x;
      l += c;
    } else {
      b[l / c] += x;
      a[l] += x;
      l++;
    }
  }
}

void solve() {
  int a[maxn], b[c], add[c] = {0};
  int n;

  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    b[i / c] += a[i];
  }

  int q;
  cin >> q;

  while (q--) {
    int t, x, y, d;
    cin >> t;

    switch (t) {
    case 1:
      cin >> x >> y;
      cout << sum(a, b, add, x, y) << "\n";
      break;
    case 2:
      cin >> x >> y >> d;
      upd(a, b, add, x, y, d);
    }
  }
}
