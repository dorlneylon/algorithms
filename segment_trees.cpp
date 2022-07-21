#include <bits/stdc++.h>
using namespace std;

void build(int v, int l, int r, vector<int> &st, vector<int> &A) {
    if (r-l == 1) {
        st[v] = A[l];
        return;
    }
    int m = (l+r)/2;
    build(2*v+1, l, m, st, A);
    build(2*v+2, m, r, st, A);
    st[v] = max(st[2*v+1], st[2*v+2]);
}

int take_max(int v, int l, int r, vector<int> &st, int lx, int rx) {
    if (lx <= l && rx >= r)
        return st[v];
    if (lx >= r || rx <= l)
        return -1;
    int m = (l+r)/2;
    int lt = take_max(2*v+1, l, m, st, lx, rx);
    int rt = take_max(2*v+2,m, r,st, lx, rx);
    return max(lt, rt);
}

int main() {
    int n, l, r;
    cin >> n;
    cin >> l >> r;
    vector <int> st(4*n);
    vector <int> A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];
    build(0,0,n,st,A);
    cout << take_max(0, 0, n, st, l-1, r);
}