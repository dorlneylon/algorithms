// https://acmp.ru/index.asp?main=task&id_task=144     задача на отработку

#include <bits/stdc++.h>
using namespace std;

typedef complex<double> base;
const double PI = acos(-1);

void fft(vector<base> &a, bool invert) {
    int n = (int) a.size();
    if (n == 1) return;

    // разобьем многочлен на 2: с четными (y0) и нечетными (y1) коэффами
    vector<base> y0(n/2),  y1(n/2);
    for (int i=0, j=0; i<n; i+=2, ++j) {
        y0[j] = a[i];
        y1[j] = a[i+1];
    }
    fft(y0, invert);
    fft(y1, invert);

    double ang = 2*PI/n * (invert ? -1 : 1);
    base w(1), wn(cos(ang), sin(ang));
    for (int i=0; i<n/2; ++i) {
        a[i] = y0[i] + w * y1[i];
        a[i+n/2] = y0[i] - w * y1[i];
        if (invert)
            a[i] /= 2,  a[i+n/2] /= 2;
        w *= wn;
    }
}

void multiply (const vector<int> &a, const vector<int> &b, vector<int> &res) {
    // скопируем массивы в комплексный тип
    vector<base> A (a.begin(), a.end()),  B(b.begin(), b.end());
    size_t n = 1;

    // доводим размер до степени двойки
    while (n < max(a.size(), b.size()))  n <<= 1;
    n <<= 1;

    A.resize(n),  B.resize(n);

    fft (A, false),  fft (B, false);

    for (size_t i=0; i<n; ++i)
        A[i] *= B[i];

    fft (A, true);

    res.resize(n);

    for(size_t i=0; i<n; ++i)
        res[i] = int (A[i].real() + 0.5);
}

int main() {
    string n, k;
    cin >> n >> k;

    // проверка на 0
    if (n == "0" || k == "0")
        cout << "0",
        exit(0);

    // заносим числа в массив в обратном порядке
    vector<int> a(n.size()), b(k.size());
    for (int i = 0; i < n.size(); i++) {
        a[i] = n[n.size()-i-1]-'0';
    }
    for (int i = 0; i < k.size(); i++) {
        b[i] = k[k.size()-i-1]-'0';
    }

    vector<int> res;
    multiply(a,b,res);

    int carry = 0;
    for (size_t i=0; i<res.size(); i++) {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }

    // заведем флаг чтобы опознать незначащие нули и избавиться от них
    int f = 0;
    for (int i = 0; i < res.size(); i++) {
        if (!f && res[res.size()-i-1]!=0) f++;
        if (f) cout << res[res.size()-i-1];
    }

}