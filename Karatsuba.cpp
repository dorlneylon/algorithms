//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#pragma GCC "arch=native"
#include <bits/stdc++.h>
using namespace std;

typedef __int32_t  i32;
typedef __uint32_t u32;
typedef __uint64_t u64;
typedef __int64_t  i64;
typedef __int8_t   i8;

const u32 base = 1e9;
const u32 base_digits = 9;

void karatsuba(i64 *a, u32 n, i64 *b, u32 m, i64 *c) {
    if (std::min(n,m) <= 32) {
        for (u32 i = 0; i < n; i++)
            for (u32 j = 0; j < m; j++) {
                c[i + j] += a[i] * b[j];
            }
        return;
    }

    if (n != m) {
        if (n < m)
            swap(a, b),
            swap(n,m);

        karatsuba(a, m, b, m, c);
        karatsuba(a + m, n - m, b, m, c + m);
        return;
    }

    if (n&1) {
        karatsuba(a+1, n-1, b+1, n-1, c+2);
        for (u32 i = 1; i < n; i++)
            c[i] += a[0] * b[i] + a[i] * b[0];
        c[0] += a[0]*b[0];
        return;
    }

    const u32 k = n/2;
    i64 l[k], r[k], t[n];
    memset(t, 0, sizeof(i64)*n);
    for (u32 i = 0; i < k; i++)
        l[i] = a[i] + a[i+k], r[i] = b[i] + b[i+k];
    karatsuba(l, k, r, k, t); // t = (a0+a1)(b0+b1)
    karatsuba(a, k, b, k, c); // p0 = a0b0
    karatsuba(a+k, k, b+k, k, c+n); // p1 = a1b1

    for (u32 i = 0; i < k; i++) {
        const i64 tmp = c[i + k];
        c[i+k] += t[i] - c[i] - c[i+n];
        c[i+n] += t[i+k] - tmp - c[i+n+k];
    }
}

vector<i64> mul(vector<i64> a, vector<i64> b) {
    vector<i64> res(a.size() + b.size(), 0);
    karatsuba((i64*)&a[0], a.size(), (i64*)&b[0], b.size(), (i64*)&res[0]);
    i64 carry = 0;
    for (u32 i = 0; i < res.size(); i++) {
        res[i] += carry;
        carry = res[i] / base;
        res[i] %= base;
    }
    while (res.size() > 1 && res.back() == 0)
        res.pop_back();
    return res;
}


int main() {
    string s;
    u32 t;
    cin >> t;
    while (t--) {
        cin >> s;
        vector<i64> a;
        for (i32 i = (i32)s.size(); i > 0; i-=base_digits)
            if (i < base_digits)
                a.push_back(atoll(s.substr(0, i).c_str()));
            else
                a.push_back(atoll(s.substr(i-base_digits, base_digits).c_str()));

        cin >> s;
        vector<i64> b;
        for (i32 i = (i32)s.size(); i > 0; i-=base_digits)
            if (i < base_digits)
                b.push_back(atoll(s.substr(0, i).c_str()));
            else
                b.push_back(atoll(s.substr(i-base_digits, base_digits).c_str()));

        vector<i64> c = mul(a, b);
        printf("%llu", c.back());
        for (i32 i = (i32)c.size()-2; i >= 0; i--)
            printf("%0*llu", base_digits, c[i]);
        printf("\n");
    }
}