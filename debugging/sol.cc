#include "sol.hh"

void solve() {
    vector<pair<int, int>> a{{1, 2}, {3, 4}, {5, 6}};
    vector<vector<int>> b{{1, 2}, {3, 4}, {5, 6}};
    string c = "debug";
    double T = 3.4;
    debug(1, "ahah", 3, c, T);
    debug(vector<int>{1, 2, 3, 4, 5});
    debug(a);
    debug(b);
}