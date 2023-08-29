#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef uint32_t u32;
typedef uint64_t u64;
const ld pi = acosl(-1);

struct ftype {
    ld re, im;
    ftype(ld re=0, ld im=0): re(re), im(im) {}
};

inline ftype operator+(const ftype& a, const ftype& b) { return {a.re+b.re,a.im+b.im}; }
inline ftype operator-(const ftype& a, const ftype& b) { return a+ftype(-b.re,-b.im); }
inline ftype operator*(const ftype& a, const ftype& b) { return {a.re*b.re - a.im*b.im, a.re*b.im + a.im*b.re}; }
inline ftype operator/(const ftype& a, const ftype& b) { return {(a.re*b.re + a.im*b.im)/(b.re*b.re+b.im*b.im), (a.im*b.re - a.re*b.im)/(b.re*b.re+b.im*b.im)}; }

vector<uint32_t> rev;
vector<ftype> wn, _a;
ftype z;

void precalc(const uint32_t& n) {
    uint32_t logn = __lg(n);
    wn.resize(n<<1);
    wn[0] = {0, 0}, wn[1] = {1,0};
    rev.resize(n, 0);
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

void fft(vector<ftype>& a) {
    uint32_t n = a.size();
    assert((n & (n-1)) == 0);
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

void multiply(vector<uint64_t>& a, vector<uint64_t>& b, vector<uint64_t>& res) {
    uint32_t need = a.size() + b.size();
    uint32_t n = 1;
    while (n < need) n <<= 1;
    precalc(n);
    _a.resize(n);
    for (uint32_t i=0; i<n; ++i)
        _a[i] = ftype(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
    fft(_a);
    for (uint32_t i=0; i<n; ++i)
        _a[i] = _a[i] * _a[i];
    fft(_a);
    res.resize(need);
    res[0] = _a[0].im/(n<<1) + 0.5;
    for (uint32_t i=1; i<need; ++i)
        res[i] = _a[n-i].im/(n<<1) + 0.5;
}