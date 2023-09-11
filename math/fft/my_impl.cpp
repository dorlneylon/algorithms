#include "fft.hh"

struct ftype {
    ld re, im;
    ftype(ld re=0, ld im=0): re(re), im(im) {}
};

inline ftype operator+(const ftype& a, const ftype& b) { return {a.re+b.re,a.im+b.im}; }
inline ftype operator-(const ftype& a, const ftype& b) { return a+ftype(-b.re,-b.im); }
inline ftype operator*(const ftype& a, const ftype& b) { return {a.re*b.re - a.im*b.im, a.re*b.im + a.im*b.re}; }
inline ftype operator/(const ftype& a, const ftype& b) { return {(a.re*b.re + a.im*b.im)/(b.re*b.re+b.im*b.im), (a.im*b.re - a.re*b.im)/(b.re*b.re+b.im*b.im)}; }

u32 *rev;
ftype *wn, *_a;
ftype z;

void precalc(const uint32_t& n) {
    uint32_t logn = __lg(n);
    wn = new ftype[n<<1];
    wn[0] = {0, 0}, wn[1] = {1,0};
    rev = new u32[n];
    rev[0] = 0, rev[1] = 1;
    for (uint32_t i=0; i<n; ++i)
        rev[i] = (rev[i>>1]>>1) | ((i&1)<<(logn-1));
    for (uint32_t i = 1; (1 << i) < n; ++i) {
        ld ang = 2 * pi / (1 << (i + 1));
        ftype e = {cosl(ang), sinl(ang)};
        for (uint32_t j = (1 << (i - 1)); j < (1 << i); ++j)
            wn[j << 1] = wn[j], wn[(j << 1) + 1] = wn[j] * e;
    }
}

void fft(ftype *a, u32 n) {
    for (uint32_t i = 1; i < n; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (uint32_t len = 1; len < n; len <<= 1)
        for (uint32_t i = 0; i < n; i += len<<1)
            for (uint32_t j = 0; j < len; j++)
                z = a[i+j+len] * wn[len+j],
                a[i+j+len] = a[i+j] - z,
                a[i+j] = a[i+j] + z;
}

void dealloc() {
    delete[] wn;
    delete[] rev;
    delete[] _a;
}

void multiply(u64* a, u32 n, u64* b, u32 m, u64 *res) {
    u32 need = n + m;
    u32 B = 1;
    while (B < need)
        B <<= 1;
    precalc(B);
    _a = new ftype[B];
    for (u32 i=0; i<B; ++i)
        _a[i] = ftype(i < n ? a[i] : 0, i < m ? b[i] : 0);
    fft(_a, B);
    for (u32 i=0; i<B; ++i)
        _a[i] = _a[i] * _a[i];
    fft(_a, B);
    res[0] = _a[0].im/(B<<1) + 0.5;
    for (u32 i=1; i<need; ++i)
        res[i] = _a[B-i].im/(B<<1) + 0.5;
    dealloc();
}