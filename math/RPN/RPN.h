#include <bits/stdc++.h>
using namespace std;

template <typename T> void __print(T x) { cerr << x; }

template <typename T> void __print(stack<T> x) {
  cerr << "[ ";
  stack<T> copy(x);
  while (!copy.empty()) {
    __print(copy.top());
    copy.pop();
    if (!copy.empty())
      cout << ", ";
  }
  cerr << " ]";
}

template <typename T> void __print(vector<T> x) {
  cerr << "[ ";
  for (auto it = x.begin(); it != x.end(); ++it) {
    if (it != x.begin())
      cerr << ", ";
    __print(*it);
  }
  cerr << " ]";
}

void debug_out() { cerr << endl; }

template <typename H, typename... T> void debug_out(H h, T... t) {
  cerr << " ";
  __print(h);
  debug_out(t...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)


string infixToRPN(const string &);
int calcExpression(const string &);

int main() {
  int t;
  cin >> t;
  cin.ignore();
  while (t--) {
    string s;
    getline(cin, s);
    debug(s);
    cout << infixToRPN(s) << endl;
    cout << calcExpression(s) << endl;
  }
  return 0;
}
