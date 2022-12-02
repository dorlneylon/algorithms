#include <iostream>
#include <vector>
using namespace std;

vector<int> a;

struct segtree {
	int lb, rb;
	int s = 0, assign = -1;
	segtree *l = nullptr, *r = nullptr;

	segtree(int lb, int rb): lb(lb), rb(rb) {
		if (lb == rb - 1) s = a[lb];
		else {
			int mb = (lb + rb) / 2;
			l = new segtree(lb, mb);
			r = new segtree(mb, rb);
			s = l->s + r->s;
		}
	}
	
	void add(int k, int x) {
		push();
		s += x;

		if (l) {
			if (k < l->rb) l->add(k, x);
			else r->add(k, x);
		}
	}

	int sum(int lq, int rq) {
		push();
		if (lb >= lq && rb <= rq) return s;
		if (max(lb, lq) >= min(rb, rq)) return 0;
		return l->sum(lq, rq) + r->sum(lq, rq);
	}

	void push() {
		if (assign != -1) {
			s += (rb - lb) * assign;
			if (l) {
				l->assign = assign;
				r->assign = assign;
			}
			assign = -1;
		}
	}

	void add(int lq, int rq, int x) {
		push();
		if (lb >= lq && rb <= rq)
			assign = x;
		else if (l && max(lb, lq) < min(rb, rq)) {
			l->add(lq, rq, x);
			r->add(lq, rq, x);
		}
	}
};

int main() {
	int n, q;
	cin >> n >> q;
	a.resize(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	segtree *s = new segtree(0,n);
	while (q--) {
		int t, x, y;
		cin >> t >> x >> y;
		if (t == 1) s->add(x, y);
		if (t > 1) s->add(x, y, t);
		else cout << s->sum(x, y) << endl;
	}
}
