#include <bits/stdc++.h>
using namespace std;

vector<vector<int32_t>> a;

void gauss() {
    if (a.empty()) return;

    uint32_t n = a[0].size();
    uint32_t m = a.size();
    uint32_t rank = 0;

    for (uint32_t j = 0; j < n; ++j) {
        bool pivotFound = false;
        for (uint32_t i = rank; i < m; ++i) {
            if (a[i][j] != 0) {
                swap(a[i], a[rank]);
                pivotFound = true;
                break;
            }
        }
        if (!pivotFound) continue;
        rank++;

        for (uint32_t k = j; k < n; ++k) {
            a[rank - 1][k] /= a[rank - 1][j];
        }

        for (uint32_t r = rank; r < m; ++r) {
            for (uint32_t k = j; k < n; ++k) {
                a[r][k] -= a[rank - 1][k] * a[r][j];
            }
        }
    }
}

int main() {
    uint32_t n, m;
    scanf("%u%u", &m, &n);
    a.resize(m, vector<int32_t>(n));

    for (uint32_t i = 0; i < m; ++i)
        for (uint32_t j = 0; j < n; ++j)
            scanf("%d", &a[i][j]);

    gauss();
    for (uint32_t i = 0; i < a.size(); ++i)
        for (uint32_t j = 0; j < a[i].size(); ++j)
            cout << a[i][j] << " \n"[j == a[i].size() - 1];
}