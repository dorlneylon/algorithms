#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int t[N], a[N], n, m;

int sum(int r) {
	int res = 0;
	for (; r > 0; r -= r & -r)
		res += t[r];
	return res;
}

int sum(int l, int r) {
	return sum(r) - sum(l - 1);
}

void add(int k, int x) {
	for (; k <= n; k += k & -k)
		t[k] += x;
}

void init() {
    for (int i = 1; i <= n; ++i)
        add(i, a[i]);
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
    init();

    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) add(l, r);
        else cout << sum(l, r) << "\n";
    }
}
