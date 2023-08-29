#include <bits/stdc++.h>
using namespace std;

int k;
string s;
vector<string> vars;
string t;

void combinations(int start) {
    if (t.size() == k) {
        vars.push_back(t);
        return;
    }

    for (int i = start; i < s.size(); i++) {
        t += s[i];
        combinations(i+1);
        t.pop_back();
    }
}

int main() {
    cin >> s >> k;
    combinations(0);
    for (auto u:vars) cout << u << "\n";
}