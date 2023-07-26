#include <bits/stdc++.h>
using namespace std;

const int32_t N = 100 + 1;
int32_t component[N];
bool indirect_cyclic_visited[N];
int8_t direct_cyclic_visited[N];
int8_t colors[N];
vector<vector<uint32_t>> adjList;

// n stores the current number of components
void adjacency_components(uint32_t v, int32_t n) {
    component[v] = n;

    for (uint32_t u:adjList[v])
        if (!component[u]) adjacency_components(u, n);
}

bool is_cyclic_indirected(uint32_t v, uint32_t p = -1) {
    if (indirect_cyclic_visited[v]) return true;
    indirect_cyclic_visited[v] = true;
    for (auto u:adjList[v])
        if (u != p && is_cyclic_indirected(u, v)) return true;
    return false;
}

bool isBipartite(uint32_t v, int8_t col) {
    colors[v] = col;

     for (auto u:adjList[v]) {
            if (!colors[u] && !isBipartite(u,-col)) return false;
            else if (colors[u] == col) return false;
        }
    return true;
}

bool is_cyclic_directed(uint32_t v) {
    if (direct_cyclic_visited[v]) return direct_cyclic_visited[v] != 2;
    direct_cyclic_visited[v] = 1;

    for (auto u:adjList[v])
        if (is_cyclic_directed(u)) return true;
    direct_cyclic_visited[v] = 2;
    return false;
}


int main() {
    adjList = {{1, 2}, {0, 2}, {0, 1, 3}, {2}};
    int32_t components = 0;

    // The number of adjacency components.
    // To find the number of adjacency components, we start dfs from each vertex as shown below.
    for (uint32_t i=0;i<adjList.size();i++) {
        if (!component[i]) adjacency_components(i, ++components);
    }
    cout << "The graph's got " << components << " adjacency components\n";

    // The number of cycles in indirect graph.
    // Shorter implementation in comparison with directed graphs. Start DFS from each unused vertex.
    for (uint32_t v=0;v<adjList.size();++v)
        if (!indirect_cyclic_visited[v] && is_cyclic_indirected(v)) {
            cout << "The graph is cyclic\n";
            break;
        }

    // The number of cycles in directed graph.
    // Start DFS from each unused vertex.
    for (uint32_t v=0;v<adjList.size();++v) {
        if (!direct_cyclic_visited[v] && is_cyclic_directed(v)) {
            cout << "The graph is cyclic\n";
            break;
        }
    }

    // Check if the graph is bipartite.
    // The implementation may require to start DFS from each adjacency component.
    for (uint32_t v=0;v<adjList.size();++v)
        if (!colors[v] && !isBipartite(v, 1)) {
            cout << "The graph is not bipartite\n";
            break;
        }

    return 0;
}