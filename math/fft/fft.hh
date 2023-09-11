#include <bits/stdc++.h>
using namespace std;

#ifndef N
#define N 1e5
#define Q 1
#endif

typedef long double ld;
typedef uint32_t u32;
typedef uint64_t u64;
const ld pi = acosl(-1);
const u32 BASE = 1e6;
const u32 BASE_DIGITS = 6;

void multiply(u64*,u32,u64*,u32,u64*);

int main() {
    char* s = new char[N+1];
    scanf("%s", s);
    uint32_t n = strlen(s), r=0;
    u64* a = new uint64_t[n/BASE_DIGITS + 1];
    for (int32_t i = n; i>0; i-=BASE_DIGITS, ++r)
        s[i] = 0, a[r] = atoll(i>=BASE_DIGITS ? s+i-BASE_DIGITS : s);
    scanf("%s", s);
    uint32_t m = strlen(s), l=0;
    u64* b = new uint64_t[m/BASE_DIGITS + 1];
    for (int32_t i = m; i>0; i-=BASE_DIGITS, ++l)
        s[i] = 0, b[l] = atoll(i>=BASE_DIGITS ? s+i-BASE_DIGITS : s);
    u64 *c = new u64[r+l];
    auto start = clock();
    multiply(a,r,b,l,c);
    cout << 1e3 * clock()-start << endl;
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] s;
    return 0;
}