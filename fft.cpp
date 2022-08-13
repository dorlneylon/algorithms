// https://acmp.ru/index.asp?main=task&id_task=144     задача на отработку

#include <bits/stdc++.h>
using namespace std;

typedef complex<double> ftype;
const double pi = acos(-1);

void fft(vector<ftype> &px, bool invert) {
    int n = (int)px.size();
    if (n == 1) return;

    // разобьем многочлен на 2: с четными (y0) и нечетными (y1) коэффами
    vector<ftype> y0(n/2), y1(n/2);

    for (int i = 0, j = 0; i < n; i+=2, j++) {
        y0[j] = px[i];
        y1[j] = px[i+1];
    }

    fft(y0, invert), fft(y1, invert);

    const double ang = 2*pi/n * (invert ? -1 : 1);
    ftype w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n/2; i++) {
        px[i] = y0[i] + w*y1[i];
        px[i+n/2] = y0[i] - w*y1[i];
        if (invert) px[i] /= 2, px[i+n/2] /= 2;
        w *= wn;
    }
}

void multiply(vector<int> &a, vector<int> &b, vector<int> &res) {
    // скопируем массивы в комплексный тип
    vector<ftype> A(a.begin(), a.end()), B(b.begin(), b.end());

    // доводим размер до степени двойки
    size_t n = 1;
    while (n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;

    A.resize(n), B.resize(n), res.resize(n);

    fft(A, false), fft(B, false);

    for (size_t i = 0; i < n; i++) {
        A[i] *= B[i];
    }

    fft(A, true);

    int carry = 0;
    for (size_t i = 0; i < n; i++) {
        res[i] = int(A[i].real() + 0.5) + carry;
        carry = res[i]/10;
        res[i] %= 10;
    }
}

int main() {
    string n, k;
    cin >> n >> k;

    if (n == "0" || k == "0")
        cout << "0",
        exit(0);

    vector<int> a(n.size()), b(k.size()), res;

    // заносим числа в массив в обратном порядке
    for (int i = 0; i < n.size(); i++) {
        a[i] = n[n.size()-i-1]-'0';
    }
    for (int i = 0; i < k.size(); i++) {
        b[i] = k[k.size()-i-1]-'0';
    }

    multiply(a, b, res);

    // заведем флаг чтобы опознать незначащие нули и избавиться от них
    int f = 0;
    for (int i = 0; i < res.size(); i++) {
        if (!f && res[res.size()-i-1]!=0) f++;
        if (f) cout << res[res.size()-i-1];
    }
}