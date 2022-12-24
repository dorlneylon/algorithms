#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct node {
  node *f, *c[2];
  int size, r;
  T sum = 0, val = 0;

  node(T val = 0) {
    f = c[0] = c[1] = nullptr;
    size = 1;
	r = 0;
	sum = val;
	this->val = val;
  }

  void push_down() {
    if (r) {
      for (int t = 0; t < 2; ++t)
        if (c[t]) c[t]->rev();
      r = 0;
    }
  }

  void update() {
    size = 1;
	sum = val;	
	for (int t = 0; t < 2; ++t)
      if (c[t]) size += c[t]->size, sum += c[t]->sum;
  }

  void rev() {
	swap(c[0], c[1]);
    r ^= 1;
  }
};

template <class T, int MAXSIZE = 500000>
struct tree {
  T *root;
  tree() {
    root = new T(), root->c[1] = new T(), root->size = 2;
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
};

const int N = 1e5;
tree<node<int>, N> t;

int main() {
	int n,q;
	cin>>n>>q;
	for(int i=0;i<n;i++){
		int x;
		cin>>x;
		t.insert(new node(x),i);
	}

	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<t.find_range(l,r)->sum<<endl;
	}

}
