#include <bits/stdc++.h>
using namespace std;

const uint64_t BASE = 1e6;
const uint64_t BASE_DIGITS = 6;

namespace fft {
    typedef long double ld;

    struct ftype {
        ld re, im;
        ftype(ld re = 0, ld im = 0) : re(re), im(im) {}
    };

    inline ftype operator+(const ftype& a, const ftype& b) { return ftype(a.re+b.re,a.im+b.im); }
    inline ftype operator-(const ftype& a, const ftype& b) { return ftype(a.re-b.re,a.im-b.im); }
    inline ftype operator*(const ftype& a, const ftype& b) { return ftype(a.re*b.re-a.im*b.im,a.im*b.re+a.re*b.im); }
    inline ftype conj(const ftype& a) { return ftype(a.re, -a.im); }

    uint32_t base = 1;
    ftype* wn;
    uint32_t* rev;
    const ld pi = acosl(-1);

    void ensure_base(uint32_t nb) {
        if (nb <= base) {
            return;
        }
        rev = new uint32_t[1<<nb];
        rev[0] = 0, rev[1] = 1;
        for (int i = 0; i < (1 << nb); i++)
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nb - 1));
        wn = new ftype[1<<nb];
        wn[0] = {0,0}, wn[1] = {1,0};
        while (base < nb) {
            ld angle = 2 * pi / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                wn[i << 1] = wn[i];
                ld angle_i = angle * (2 * i + 1 - (1 << base));
                wn[(i << 1) + 1] = ftype(cosl(angle_i), sinl(angle_i));
            }
            base++;
        }
    }

    ftype* fa;
    uint32_t fas = 0;

    void fft(ftype* a, int32_t n = -1) {
        if (n == -1) n = fas;
        assert((n & (n - 1)) == 0);
        uint32_t zeros = __builtin_ctz(n);
        ensure_base(zeros);
        uint32_t shift = base - zeros;
        for (uint32_t i = 0; i < n; i++)
            if (i < (rev[i] >> shift))
                swap(a[i], a[rev[i] >> shift]);
        for (uint32_t k = 1; k < n; k <<= 1) {
            for (uint32_t i = 0; i < n; i += 2 * k) {
                for (uint32_t j = 0; j < k; j++) {
                    ftype z = a[i + j + k] * wn[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }

    void dealloc() {
        delete[] fa;
        delete[] rev;
        delete[] wn;
        fas = 0;
    }

    uint64_t* multiply(uint64_t* a, uint64_t* b, uint32_t as, uint32_t bs) {
        uint32_t need = as + bs - 1;
        uint32_t nb = 1;
        while ((1 << nb) < need) nb++;
        rev = new uint32_t[2];
        rev[0] = 0, rev[1] = 1;
        wn = new ftype[2];
        wn[0] = {0,0}, wn[1] = {1,0};
        ensure_base(nb);
        uint32_t sz = 1 << nb;
        fa = new ftype[sz];
        fas = sz;
        for (uint32_t i = 0; i < sz; i++) {
            uint64_t re = (i < as ? a[i] : 0);
            uint64_t im = (i < bs ? b[i] : 0);
            fa[i] = ftype(re, im);
        }
        fft(fa,sz);
        ftype r(0, -0.25 / (sz >> 1));
        for (uint32_t i = 0; i <= (sz >> 1); i++) {
            uint32_t j = (sz - i) & (sz - 1);
            ftype z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
            if (i != j)
                fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
            fa[i] = z;
        }
        for (uint32_t i = 0; i < (sz >> 1); i++) {
            ftype A0 = (fa[i] + fa[i + (sz >> 1)]) * ftype(0.5, 0),
                  A1 = (fa[i] - fa[i + (sz >> 1)]) * ftype(0.5, 0) * wn[(sz >> 1) + i];
            fa[i] = A0 + A1 * ftype(0, 1);
        }
        fft(fa, sz >> 1);
        uint64_t* res = new uint64_t[need];
        for (uint32_t i = 0; i < need; i++)
            if (i % 2 == 0)
                res[i] = fa[i >> 1].re + 0.5;
            else
                res[i] = fa[i >> 1].im + 0.5;
        dealloc();
        return res;
    }
}

int main() {
    char* s = new char[1000001];
    uint32_t t;
    scanf("%u",&t);
    while (t--) {
        scanf("%s",s);
        uint32_t n = strlen(s), r=0;
        uint64_t* a = new uint64_t[n/BASE_DIGITS + 1];
        for (int32_t i = n; i>0; i-=BASE_DIGITS, ++r)
            s[i] = 0, a[r] = atoll(i>=BASE_DIGITS ? s+i-BASE_DIGITS : s);
        scanf("%s",s);
        uint32_t m = strlen(s), l=0;
        uint64_t* b = new uint64_t[m/BASE_DIGITS + 1];
        for (int32_t i = m; i>0; i-=BASE_DIGITS, ++l)
            s[i] = 0, b[l] = atoll(i>=BASE_DIGITS ? s+i-BASE_DIGITS : s);
        uint64_t* c = fft::multiply(a,b,r,l);
        uint32_t need = l+r-1;
        uint64_t carry = 0;
        for (uint32_t i = 0; i < need; i++)
            c[i] += carry, carry = c[i] / BASE, c[i] %= BASE;
        printf("%llu",c[need-1]);
        for (uint32_t i = need-1; i>0; --i)
            printf("%06llu",c[i-1]);
        printf("\n");
        delete[] a;
        delete[] b;
        delete[] c;
    }

    delete[] s;
    return 0;
}