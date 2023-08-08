#include <bits/stdc++.h>
using namespace std;

const uint64_t BASE = 1e9;
const uint64_t BASE_DIGITS = 9;

void rec_kara(uint64_t* a, const uint32_t& one, uint64_t* b, const uint32_t& two, uint64_t* r) {
    if(min(one, two) <= 20) { // если размер маленький, то быстрее умножать за квадрат
        for (uint32_t i = 0; i < one; ++i)
            for (uint32_t j = 0; j < two; ++j)
                r[i+j] += a[i] * b[j];
        return;
    }
    const uint32_t x = min(one, two);
    // запускаемся рекурсивно, выравнивая размеры массивов
    if (one < two) rec_kara(a, x, b + x, two - x, r + x);
    if (two < one) rec_kara(a + x, one - x, b, x, r + x);
    const uint32_t n = (x+1)>>1, right = x>>1;
    uint64_t* tu = new uint64_t[n<<1];
    // запускаемся рекрурсивно на половинках массивов
    rec_kara(a, n, b, n, tu);
    // переносим в r
    for (uint32_t i=0;i<((n<<1)-1);++i)
        r[i] += tu[i], r[i+n] -= tu[i], tu[i] = 0;
    // аналогично для второй половины
    rec_kara(a + n, right, b + n, right, tu);
    for (uint32_t i=0;i<(right<<1)-1;++i)
        r[i+n] -= tu[i], r[i+2*n] += tu[i];
    tu[n-1] = a[n-1]; tu[2*n-1] = b[n-1];
    for (uint32_t i=0;i<right;++i)
        tu[i] = a[i]+a[i+n], tu[i+n] = b[i]+b[i+n];
    rec_kara(tu, n, tu + n, n, r + n);
    delete[] tu;
}

uint64_t* karatsuba(uint64_t* a, uint64_t* b, const uint32_t& n, const uint32_t& m) {
    assert(n>0 && m>0 && "Invalid size of arrays");
    uint64_t* r = new uint64_t[n+m-1];
    rec_kara(a,n,b,m,r);
    return r;
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
        uint64_t* c = karatsuba(a,b,r,l);
        uint32_t need = l+r-1;
        uint64_t carry = 0;
        for (uint32_t i = 0; i < need; i++)
            c[i] += carry, carry = c[i] / BASE, c[i] %= BASE;
        if (carry) printf("%llu",carry);
        printf("%llu",c[need-1]);
        for (uint32_t i = need-1; i>0; --i)
            printf("%09llu",c[i-1]);
        printf("\n");
        delete[] a;
        delete[] b;
        delete[] c;
    }

    delete[] s;
    return 0;
}