#include <bits/stdc++.h>
using namespace std;

const int N = 300;
const int V = N * N;
const int E = 4 * V + 1;

int h, w, a, b;                      // height, width, a, b
int e = 1, head[V], next[E], to[E];
int color = 1, used[V], p[V];

void add(int a, int b) {
    next[e] = head[a], to[e] = b, head[a] = e++;
}

int dfs(int v) {
    used[v] = color;
    for (int x, e = head[v]; e; e = next[e]) {
        if (p[x = to[e]] == -1 || (used[p[x]] != color && dfs(p[x]))) {     //  if not matched or can improve
            p[x] = v, p[v] = x;                                             //  match and return 1
            return 1;                                                       //  else return 0
        }
    }
    return 0;
}

int main() {
    // test kuhn
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        add(a, b);
    }
    int ans = 0;
    memset(p, -1, sizeof(p));
    for (int i = 0; i < n; i++) {
        color++;
        ans += dfs(i);
    }
    cout << ans << "\n";
}