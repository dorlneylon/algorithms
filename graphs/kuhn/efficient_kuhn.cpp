#include <bits/stdc++.h>
using namespace std;

const int N = 300;
const int V = N * N;
const int E = 4 * V + 1;

int h, w, a, b;                     // height, width, a, b
int e = 1, he[V], ne[E], to[E];     // edges, head, next, to
char s[N][N + 1];                   // grid
int cc = 1, u[V], pa[V];            // color, used, parent

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};


void add(int a, int b) {
    ne[e] = he[a], to[e] = b, he[a] = e++;
}

int dfs(int v) {
    u[v] = cc;
    for (int x, e = he[v]; e; e = ne[e]) {
        if (pa[x = to[e]] == -1 || (u[pa[x]] != cc && dfs(pa[x]))) { //  if not matched or can improve
            pa[x] = v, pa[v] = x;                                    //  match and return 1
            return 1;                                                //  else return 0
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
    memset(pa, -1, sizeof(pa));
    for (int i = 0; i < n; i++) {
        cc++;
        ans += dfs(i);
    }
    cout << ans << "\n";
}