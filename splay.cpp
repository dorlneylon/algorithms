#include "bits/stdc++.h"
using namespace std;


namespace allo {

template <class T, int MAXSIZE>
struct array {
  T v[MAXSIZE], *top;
  array() : top(v) {}
  T *alloc(const T &val = T()) { return &(*top++ = val); }
  void dealloc(T *p) {}
};

template <class T, int MAXSIZE>
struct stack {
  T v[MAXSIZE];
  T *spot[MAXSIZE], **top;
  stack() {
    for (int i = 0; i < MAXSIZE; ++i) spot[i] = v + i;
    top = spot + MAXSIZE;
  }
  T *alloc(const T &val = T()) { return &(**--top = val); }
  void dealloc(T *p) { *top++ = p; }
};

}

namespace splay {

template <class T>
struct node {
  T *f, *c[2];
  int size;
  node() {
    f = c[0] = c[1] = nullptr;
    size = 1;
  }
  void push_down() {}
  void update() {
    size = 1;
    for (int t = 0; t < 2; ++t)
      if (c[t]) size += c[t]->size;
  }
};

template <class T>
struct reversible_node : node<T> {
  int r;
  reversible_node() : node<T>() { r = 0; }
  void push_down() {
    node<T>::push_down();
    if (r) {
      for (int t = 0; t < 2; ++t)
        if (node<T>::c[t]) node<T>::c[t]->reverse();
      r = 0;
    }
  }
  void update() { node<T>::update(); }
  // Reverse the range of this node.
  void reverse() {
    std::swap(node<T>::c[0], node<T>::c[1]);
    r = r ^ 1;
  }
};

template <class T, int MAXSIZE = 500000,
          class alloc = allo::array<T, MAXSIZE + 2>>
struct tree {
  alloc pool;
  T *root;
  // Get a new node from the pool.
  T *new_node(const T &val = T()) { return pool.alloc(val); }
  tree() {
    root = new_node(), root->c[1] = new_node(), root->size = 2;
    root->c[1]->f = root;
  }
  // Helper function to rotate node.
  void rotate(T *n) {
    int v = n->f->c[0] == n;
    T *p = n->f, *m = n->c[v];
    if (p->f) p->f->c[p->f->c[1] == p] = n;
    n->f = p->f, n->c[v] = p;
    p->f = n, p->c[v ^ 1] = m;
    if (m) m->f = p;
    p->update(), n->update();
  }
  // Splay n so that it is under s (or to root if s is null).
  void splay(T *n, T *s = nullptr) {
    while (n->f != s) {
      T *m = n->f, *l = m->f;
      if (l == s)
        rotate(n);
      else if ((l->c[0] == m) == (m->c[0] == n))
        rotate(m), rotate(n);
      else
        rotate(n), rotate(n);
    }
    if (!s) root = n;
  }
  // Get the size of the tree.
  int size() { return root->size - 2; }
  // Helper function to walk down the tree.
  int walk(T *n, int &v, int &pos) {
    n->push_down();
    int s = n->c[0] ? n->c[0]->size : 0;
    (v = s < pos) && (pos -= s + 1);
    return s;
  }
  // Insert node n to position pos.
  void insert(T *n, int pos) {
    T *c = root;
    int v;
    ++pos;
    while (walk(c, v, pos), c->c[v] && (c = c->c[v]))
      ;
    c->c[v] = n, n->f = c, splay(n);
  }
  // Find the node at position pos. If sp is true, splay it.
  T *find(int pos, int sp = true) {
    T *c = root;
    int v;
    ++pos;
    while ((pos < walk(c, v, pos) || v) && (c = c->c[v]))
      ;
    if (sp) splay(c);
    return c;
  }
  // Find the range [posl, posr) on the splay tree.
  T *find_range(int posl, int posr) {
    T *r = find(posr), *l = find(posl - 1, false);
    splay(l, r);
    if (l->c[1]) l->c[1]->push_down();
    return l->c[1];
  }
  // Insert nn of size nn_size to position pos.
  void insert_range(T **nn, int nn_size, int pos) {
    T *r = find(pos), *l = find(pos - 1, false), *c = l;
    splay(l, r);
    for (int i = 0; i < nn_size; ++i) c->c[1] = nn[i], nn[i]->f = c, c = nn[i];
    for (int i = nn_size - 1; i >= 0; --i) nn[i]->update();
    l->update(), r->update(), splay(nn[nn_size - 1]);
  }
  // Helper function to dealloc a subtree.
  void dealloc(T *n) {
    if (!n) return;
    dealloc(n->c[0]);
    dealloc(n->c[1]);
    pool.dealloc(n);
  }
  // Remove from position [posl, posr).
  void erase_range(int posl, int posr) {
    T *n = find_range(posl, posr);
    n->f->c[1] = nullptr, n->f->update(), n->f->f->update(), n->f = nullptr;
    dealloc(n);
  }
};

}

// TODO:
// 1. Define a node inheriting from splay::node<node> or splay::reversible_node<node>.
// 2. Add the values you want to use.
// 3. Overload the constructor, push_down, update, (potentially) reverse.
// (Do not forget to call the base method.)
// 4. Add whatever operations you want.
// 5. Define a tree with splay::tree<node, MAXSIZE, allo::stack<node, MAXSIZE + 2>> t;

const int MAXSIZE = 200000;

struct node: splay::reversible_node<node> {
  int val, val_min, label_add, sum;
  node(int v = 0) : splay::reversible_node<node>(), val(v), sum(v) { val_min = label_add = 0; }
  // Add v to the subtree.
  void add(int v) {
    val += v;
    val_min += v;
    label_add += v;
	sum += v;
  }
  void push_down() {
    splay::reversible_node<node>::push_down();
    for (int t = 0; t < 2; ++t) if (c[t]) c[t]->add(label_add);
    label_add = 0;
  } 
  void update() {
    splay::reversible_node<node>::update();
    val_min = val;
	sum = val + (c[0] ? c[0]->sum : 0) + (c[1] ? c[1]->sum : 0);
	for (int t = 0; t < 2; ++t) if (c[t]) val_min = min(val_min, c[t]->val_min);
  }
};

splay::tree<node, MAXSIZE, allo::stack<node, MAXSIZE + 2>> t;

int main() {
	int n,m, op;
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		int x;
		cin >> x;
		t.insert(new node(x), i);
	}

	while (m--) {
		cin >> op;
		if (op == 1) {
			int l, r, x;
			cin >> l >> r >> x;
			node *n = t.find_range(l, r + 1);
			n->add(x);
		} else if (op == 0) {
			int l,r;
			cin >> l >> r;
			cout << t.find_range(l, r)->sum << endl;
		} else if (!op) {
			int l,r;
			cin >> l >> r;
			cout << t.find_range(l, r)->val_min << endl;
		} else if (op == 3) {
			int l,r;
			cin >> l >> r;
			t.find_range(l, r)->reverse();
		} else if (op == 4) {
			int l,r;
			cin >> l >> r;
			cout << t.find_range(l, r)->val << endl;
		}
	}
}

