#pragma GCC "arch=native"
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("03")
#include <bits/stdc++.h>
using namespace std;
typedef int32_t i32;
typedef uint64_t u64;

// one-based indexing

const u64 N = 1e5;

inline constexpr i32 hole(i32 k) {
    return k + (k >> 10);
}

i32 t[hole(N) + 1];

void add(i32 k, i32 x) {
    for (; k <= N; k += k & -k)
        t[hole(k)] += x;
}

i32 sum(i32 k) {
    i32 res = 0;
    for (; k != 0; k &= k - 1)
        res += t[hole(k)];
    return res;
}

int main() {
    i32 n, q;
    cin >> n >> q;
    for (i32 i = 0; i < n; i++) {
        int x;
        cin >> x;
        add(i, x);
    }
    while (q--) {
        i32 t;
        cin >> t;
        if (t == 1) {
            i32 k, x;
            cin >> k >> x;
            add(k, x);
        } else {
            i32 l, r;
            cin >> l >> r;
            cout << sum(r) - sum(l - 1) << '\n';
        }
    }
    return 0;
}
