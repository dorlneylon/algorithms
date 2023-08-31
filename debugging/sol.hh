#ifndef __SOL_H
#define __SOL_H
#include <bits/stdc++.h>
using namespace std;


// define __print for required types
template<typename T> void __print(T x) { cerr << x; }
template<typename T, typename V> void __print(pair<T, V> x) { cerr << "{"; __print(x.first); cerr << ", "; __print(x.second); cerr << "}"; }
template<typename T> void __print(vector<T> x) { cerr << "[ "; for (auto it = x.begin(); it != x.end(); ++it) { if (it != x.begin()) cerr << ", "; __print(*it); } cerr << " ]"; }
// ...

void debug_out() {
    cerr << endl;
}

template<typename H, typename... T>
void debug_out(H h, T... t) {
    cerr << " ";
    __print(h);
    debug_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

// g++ -std=c++11 -Wall -Wextra -O3 -fsanitize=address -ffast-math sol.cc -o sol
// now it can be run like this:
// ./sol < in > out 2> debug
// or like this:
// ./sol < in > out

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    solve();
}

#endif