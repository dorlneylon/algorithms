#pragma GCC "arch=native"
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef uint64_t u64;
typedef uint32_t u32;
typedef int32_t i32;
typedef i32 vec __attribute__ (( vector_size(32) )); // vector of 8 int32_t

const u64 N = 1e5;
const u32 b = 4, B = (1 << b); // i32 = 4 bytes. the tree is split into B vecs of size B

constexpr int round(int k) {
    return k & ~(B - 1); // = k / B * B
}

constexpr u32 height(u32 n) {
    return (n <= B ? 1 : height(n / B) + 1);
}

constexpr u32 offset(u32 h) { // where the h'th level starts
    i32 s = 0; u32 n = N;
    while (h--) {
        n = (n + B - 1) / B;
        s += n * B;
    }
    return s;
}

constexpr u32 H = height(N);

struct Precalc {
    alignas(64) int mask[B][B];

    constexpr Precalc() : mask{} {
        for (int k = 0; k < B; k++)
            for (int i = 0; i < B; i++)
                mask[k][i] = (i > k ? -1 : 0);
    }
};

constexpr Precalc T;

alignas(64) i32 t[offset(H)]; // tree

i32 sum(i32 k) {
    i32 res = 0;
    for (i32 h = 0; h < H; h++)
        res += t[offset(h) + (k >> (h * b))]; // k >> (h * b) is the index of the k'th element on h'th level
    return res;
}

void add(i32 k, i32 _x) {
    vec x = _x + vec{}; // broadcast _x to all 8 elements of x
    for (int h = 0; h < H; h++) {
        auto l = (vec*) &t[offset(h) + round(k)]; // offset(h) + round(k) tells the index of the first element on the h'th level
        auto m = (vec*) T.mask[k % B]; // whether to add x to the first element on the h'th level
        for (i32 i = 0; i < B / 8; i++)
            l[i] += x & m[i];
        k >>= b;
    }
}

i32 sum(i32 l, i32 r) {
    return sum(r) - sum(l);
}

int main() {
    add(0,6);
    add(1,2);
    add(2,3);
    add(3,4);
    add(4,5);
    cout << sum(3,5) << " " << endl;
}