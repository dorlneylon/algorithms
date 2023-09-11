#include "floyd.hh"

inline u32 __min(u32 a, u32 constexpr b) {
    return a < b ? a : b;
}

inline void kernel(u32* __restrict__ a, u32* __restrict__ b, u32 c, u32 n) {
    for (u32 i = 0; i < n; ++i)
        a[i] = __min(a[i], b[i]+c);
}

void floyd(u32 *d, u32 n) {
    for (u32 k = 0; k < n; ++k)
        for (u32 i = 0; i < n; ++i)
            kernel(d + i*n, d + k*n, d[i*n + k], n);
}

// rest stays the same