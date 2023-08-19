#include <bits/stdc++.h>
using namespace std;

const uint64_t BASE = 1e9;
const uint64_t BASE_DIGITS = 9;
const uint32_t maxn = 1e5;

void K(uint64_t *x, uint32_t n, uint64_t *y, uint32_t m, uint64_t *z) {
    if (n < m) {
        std::swap(n, m);
        std::swap(x, y);
    }
    std::fill(z, z + n + m, 0);
    if (m <= 32) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                z[i + j] += x[i] * y[j];
        return;
    }
    uint32_t m1 = (n + 1) / 2;
    uint32_t n1 = std::min(m1, m);
    for (uint32_t i = 0; i + m1 < n; ++i)
        x[i] += x[i + m1];
    for (uint32_t j = 0; j + m1 < m; ++j)
        y[j] += y[j + m1];
    K(x, m1, y, n1, z + m1);
    for (uint32_t i = 0; i + m1 < n; ++i)
        x[i] -= x[i + m1];
    for (uint32_t j = 0; j + m1 < m; ++j)
        y[j] -= y[j + m1];
    uint64_t p[2 * m1 + 2];
    K(x, m1, y, n1, p);
    for (uint32_t i = 0; i < m1 + n1; ++i)
        z[i] += p[i],
                z[i + m1] -= p[i];
    K(x + m1, n - m1, y + m1, m - n1, p);
    for (uint32_t i = 0; i < n + m - m1 - n1; ++i)
        z[i + m1] -= p[i],
                z[i + 2 * m1] += p[i];
};

void mul(uint64_t *a, uint32_t n, uint64_t *b, uint32_t m, uint64_t *c, uint32_t &need) {
    assert(n > 0 && m > 0);
    need = n + m;
    K(a, n, b, m, c);
    uint64_t carry = 0;
    for (uint32_t i = 0; i < n + m; ++i) {
        c[i] += carry;
        carry = c[i] / BASE;
        c[i] %= BASE;
    }
    while (c[need-1] == 0 && need > 1) --need;
}

int main() {
    char* s = new char[100001];
    uint64_t a[maxn], b[maxn], c[maxn];
    uint32_t t;
    scanf("%u",&t);
    while (t--) {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        scanf("%s",s);
        uint32_t n = strlen(s), r=0;
        for (int32_t i = n; i>0; i-=BASE_DIGITS, ++r)
            s[i] = 0, a[r] = atoll(i>=BASE_DIGITS ? s+i-BASE_DIGITS : s);
        scanf("%s",s);
        uint32_t m = strlen(s), l=0;
        for (int32_t i = m; i>0; i-=BASE_DIGITS, ++l)
            s[i] = 0, b[l] = atoll(i>=BASE_DIGITS ? s+i-BASE_DIGITS : s);
        memset(c,0,sizeof(c));
        uint32_t need;
        mul(a,r,b,l,c,need);
        printf("%llu",c[need-1]);
        for (uint32_t i = need-1; i>0; --i)
            printf("%0*llu",BASE_DIGITS,c[i-1]);
        printf("\n");
    }
    delete[] s;
    return 0;
}

//for (uint32_t i=0; i<min(n,m)/2; ++i)
//  res[i+min(n,m)/2] += a[i] - a[i+min(n,m)/2], res[i+min(n,m)] += b[i] - b[i+min(n,m)/2];