#include <bits/stdc++.h>
using namespace std;

int n;

void eratosphenes() {
    bool sieve[n+1];
    for (int i = 2; i <= sqrt(n); i++) {
        for (int j = 2*i; j <= n; j+=i)
            sieve[j] = true;
    }
    for (int k = 2; k <= n; k++)
        if (!sieve[k]) cout << k << " ";
}

int main() {
    cin >> n;
    eratosphenes();
}