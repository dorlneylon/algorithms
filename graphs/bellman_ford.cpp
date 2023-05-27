#include <bits/stdc++.h>
#define INF 0x3f3f3f3f

const int32_t N = 1e5 + 5;

int d[N], n;

std::vector<std::pair<int32_t, int32_t>> adj[N];

void bellman_ford(int32_t v) {
	for (int32_t i = 0; i < n; ++i) {
		d[i] = INF;
	}

	d[v] = 0;

	for (int i = 0; i < n - 1; ++i) {
		for (int32_t u = 0; u < n; ++u) {
			for (uint32_t v = 0; v < adj[u].size(); ++v) {
				int32_t to = adj[u][v].first;
				int32_t w = adj[u][v].second;

				d[to] = std::min(d[to], d[u] + w);
			}
		}
	}
}

int main() {
	scanf("%d\n", &n);
	
	// вводим массив где на iй строке стоят пары u h, где u — смежная с iй вершина, h — вес их ребра.
	for (int32_t i = 0; i < n; ++i) {
		char s[256];
		std::cin.getline(s, 256);

		std::stringstream ss(s);
		int32_t u, v;

		while (ss >> u >> v) {
			adj[i].push_back({u, v});
		}
	}

	for (int32_t i = 0; i < n; ++i) {
		printf("%d: ", i);
		for (uint32_t j = 0; j < adj[i].size(); ++j) {
			printf("%d ", adj[i][j].first);
		}
		printf("\n");
	}

	// запускаем алгоритм от вершины x
	bellman_ford(0);

	// смотрим на массив d, в котором хранятся кратчайшие расстояния от вершины x до всех остальных
	for (int32_t i = 0; i < n; ++i) {
		printf("%d ", d[i]);
	}

	return 0;
}