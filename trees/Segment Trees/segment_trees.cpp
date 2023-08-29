#include <bits/stdc++.h>
using namespace std;

void build(int v, int l, int r, vector<int> &st, vector<int> &a) {
    if (r-l == 1) {
        st[v] = a[l];
        return;
    }
    int m = (l+r)/2;
    build(2*v+1, l, m, st, a);
    build(2*v+2, m, r, st, a);
    st[v] = st[2*v+1] + st[2*v + 2];
}

int take(int v, int l, int r, int lx, int rx, vector<int> &st) {
    if (lx >= r || rx <= l) {
        return 0;
    }
    if (lx <= l && rx >= r) {
        return st[v];
    }
    int m = (l+r)/2;
    int lt = take(2*v+1, l, m, lx, rx, st);
    int rt = take(2*v+2, m, r, lx, rx, st);
    return lt+rt;
}

void update(int v, int l, int r, int x, int pos, vector<int> &st) {
    if (r - l == 1) {
        st[v] = x;
        return;
    }
    int m = (l + r)/2;
    if (pos < m) {
        update(2*v+1, l, m, x, pos, st);
    }
    else {
        update(2*v+2, m, r, x, pos, st);
    }
    st[v] = st[2*v+1] + st[2*v + 2];
}

int main() {
    int n, l, r, ind, t;
    cin >> n;
    vector <int> a(n);
    vector <int> st(4*n);

    for (int i = 0; i < n; i++) cin >> a[i];

    build(0,0,n,st,a);

    cin >> l >> r;
    cout << take(0,0,n,l-1,r,st) << "\n";
    cin >> ind >> t;

    update(0,0,n,t,ind-1,st);

    cout << take(0,0,n,l-1,r,st);
}