#include <bits/stdc++.h>
using namespace std;

string s;
int n;

vector<int> z_function() {
    vector<int> z(n,0);

    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) {
            z[i] = min(z[i-l], r-i+1);
        }

        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            z[i]++;

        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    return z;
}

int main() {
    cin >> s;
    n = s.size();
    vector<int> z = z_function();
    for (int i:z) cout << i << " ";
}