#include <bits/stdc++.h>
using namespace std;

int n;
string s;

vector<int> manacher_odd() {
    vector <int> d1(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = i > r ? 1 : min(d1[l+r-i], r-i+1);
        while (i + k < n && i - k >= 0 && s[i+k] == s[i-k])
            k++;
        d1[i] = k;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    return d1;
}

vector<int> manacher_even() {
    vector<int> d2(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = i > r ? 0 : min(d2[l+r-i+1], r-i+1);
        while (i + k < n && i - k - 1 >= 0 && s[i+k] == s[i-k-1])
            k++;
        d2[i] = k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    return d2;
}

int main() {
    cin >> s;
    n = s.size();
    vector<int> a = manacher_odd();
    vector<int> b = manacher_even();

    int it = 0, mx = 0;

    for (int i = 0; i < n; i++) {
        if (2*a[i] - 1 > mx) {
            mx = 2*a[i] - 1;
            it = i - a[i] + 1;
        }
        if (2*b[i] > mx) {
            mx = 2*b[i];
            it = i-b[i];
        }
    }

    cout << s.substr(it, mx);
}