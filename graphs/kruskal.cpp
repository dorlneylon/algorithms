#include <bits/stdc++.h>
#include "./dsu.cpp"

struct edge {
    int u, v, w;
    edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const edge& e) const { // > for min spanning tree
        return w < e.w;
    }
};

int kruskal(int n, std::vector<edge>& edges) {
    init(n);
    std::sort(edges.begin(), edges.end());
    int cost = 0;
    for (edge e : edges) {
        if (leader(e.u) != leader(e.v)) {
            cost += e.w;
            unite(e.u, e.v);
        }
    }
    return cost;
}