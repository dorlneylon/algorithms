#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef complex<ld> ftype;
typedef uint32_t u32;
typedef uint64_t u64;
const ld pi = acosl(-1);

void fft(ftype* a, u32 n = 1, ftype eps) {
    if (n == 1) return;

    u32 k = n >> 1;
    fft(a, k, eps*eps);
    fft(a+k, k, eps*eps);
    ftype e = 1;
    
    for (u32 l = 0; l < k; l++) {
        ftype t = e * a[l + k];
        a[l + k] = a[l] - t; 
        a[l] = a[l] + t;
        e *= eps;
    }
}

void mul(u64* a, u32 n, u64* b, u32 m, u64 *res) {
    assert(n > 0 && m > 0);
    u32 B = 1;
    const u32 logn = __lg(n);
    while (B < n+m)
        B <<= 1;
    ftype _a[B], _b[B];
    for (u32 i = 0; i < B; ++i) {
        _a[i] = i < n ? a[i] : 0;
        _b[i] = i < m ? b[i] : 0;
    }
    for (u32 i = 0; i < n; i++) { // bit-reversal permutation
        u32 k = 0;
        for (u32 l = 0; l < logn; l++)
            k |= ((i >> l & 1) << (logn - l - 1));
        if (i < k) {
            swap(_a[i], _a[k]),
            swap(_b[i], _b[k]);
        }
    }
    fft(_a, B, polar(ld(1), 2*pi/n)); // "using polar might be 4.5x times faster"
    fft(_b, B, polar(ld(1), 2*pi/n));
    for (u32 i = 0; i < B; ++i)
        _a[i] *= _b[i];
    fft(_a, B, polar(ld(1), -2*pi/n));
    for (u32 i = 0; i < n+m; ++i)
        res[i] = _a[i].real() + 0.5;
}