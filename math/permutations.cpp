#include <bits/stdc++.h>
using namespace std;

int n;
vector <int> a;
deque <int> permutation;
vector <deque <int>> vars;
bool u[0xc3];

void permutations(int it) {
    if (it == n) {
        vars.push_back(permutation);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!u[i]) {
            u[i] = true;
            permutation.push_back(i);
            permutations(it+1);
            permutation.pop_back();
            u[i] = false;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        a.push_back(i);
    permutations(0);
    for (auto v:vars) {
        for (int k: v) cout << k << " ";
        cout << "\n";
    }
}