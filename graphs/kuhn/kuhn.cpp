#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5;

vector<int> g[maxn];    // будем хранить только рёбра из левой доли в правую
int mt[maxn];           // с какой вершиной сматчена вершина правой доли (-1, если ни с какой)
bool used[maxn];        // вспомогательный массив для поиска пути dfs-ом

// dfs возвращает, можно ли найти путь из вершины v
// в какую-нибудь вершину правой доли
// если можно, то ещё и проводит чередование
bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int u : g[v]) {
        // если вершина свободна, то можно сразу с ней соединиться
        // если она занята, то с ней можно соединиться только тогда,
        // когда из её текущей пары можно найти какую-нибудь другую вершину
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

int kuhn(int n) {
    memset(mt, -1, sizeof(mt));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        memset(used, 0, sizeof(used));
        if (dfs(i))
            ans++;
    }
    return ans;
}