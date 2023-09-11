#include "fft.hh"

typedef complex<ld> ftype;

void fft(ftype* a, u32 n, int k = 1) {
    if (n == 1) return;
    ftype a0[n/2], a1[n/2];
    for (u32 i = 0; i < n/2; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, k);
    fft(a1, k);
    double ang = k*2*pi/n;
    ftype w = {1,0}, wn = {cosl(ang), sinl(ang)};
    for (u32 i = 0; i < n/2; i++) {
        a[i] = a0[i] + w*a1[i];
        a[i+n/2] = a0[i] - w*a1[i];
        w *= wn;
    }
}

void multiply(u64* a, u32 n, u64* b, u32 m, u64* res) {
    u32 B = 1, need = n + m;
    while (B <= need) B <<= 1;
    ftype *_a = new ftype[B], *_b = new ftype[B];
    for (u32 i = 0; i < B; ++i)
        _a[i] = ftype(i < n ? a[i] : 0),
        _b[i] = ftype(i < m ? b[i] : 0);
    
    fft(_a, n);
    fft(_b, n);

    for (u32 i = 0; i < B; ++i)
        _a[i] *= _b[i];

    fft(_a, n, -1);

    for (u32 i = 0; i < need; ++i)
        res[i] = _a[i].real()/B + 0.5;

    delete[] _a, delete[] _b;
}