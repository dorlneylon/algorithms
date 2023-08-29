#include <iostream>
using namespace std;


template<typename T>
struct node {
    node *l = nullptr, *r = nullptr;
    T val, prior, mn, size, add = 0, s;
    bool rev = false;
    node(T val): val(val), prior(rand()), mn(val), size(1), s(val) {}
    ~node() {
        delete l;
        delete r;
    }
};

template<typename T, class node=node<T> >
struct treap {
    node *root = nullptr;

    T ts(node *p) {
        return p ? p->size : 0;
    }

    T tm(node *p) {
        return p ? p->mn + p->add : 1e9;
    }

    T tsum(node *p) {
        return p ? p->s + p->add : 0;
    }

    T gs(node *p) {
        return p ? ts(p->l) + ts(p->r) + 1 : 0;
    }

    void push(node *p) {
        if (!p) return;
        p->val += p->add;
        p->mn += p->add;
        p->s += p->add;
        if (p->l) p->l->add += p->add;
        if (p->r) p->r->add += p->add;
        p->add = 0;
        if (p->rev) {
            p->rev ^= 1;
            swap(p->l, p->r);
            if (p->l) p->l->rev ^= 1;
            if (p->r) p->r->rev ^= 1;
        }
    }

    void upd(node *p) {
        if (!p) return;
        p->size = ts(p->l) + ts(p->r) + 1;
        p->mn = min(tm(p->l), min(tm(p->r), p->val + p->add));
        p->s = tsum(p->l) + p->val + tsum(p->r) + p->add;
    }

    pair<node*, node*> split(node *p, T k) {
        if (!p) return {nullptr, nullptr};
        push(p);
        if (gs(p->l) < k) {
            auto [l, r] = split(p->r, k - gs(p->l) - 1);
            p->r = l;
            upd(p), upd(r);
            return {p, r};
        } else {
            auto [l, r] = split(p->l, k);
            p->l = r;
            upd(l), upd(r);
            return {l, p};
        }
    }

    node* merge(node *l, node *r) {
        push(l), push(r);
        if (!l || !r) return l ? l : r;
        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            upd(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            upd(r);
            return r;
        }
    }

    void pushBack(T val) {
        root = merge(root, new node(val));
    }

    T mnval(int lx, int rx) {
        auto [l, t] = split(root, lx);
        auto [m, r] = split(t, rx-lx+1);
        int res = m->mn;
        root = merge(l, merge(m, r));
        return res;
    }

    T get(int k) {
        auto [l, t] = split(root, k);
        auto [m, r] = split(t, 1);
        int res = m->val;
        root = merge(l, merge(m, r));
        return res;
    }

    T get(int lx, int rx) {
        auto [l, t] = split(root, lx);
        auto [m, r] = split(t, rx-lx+1);
        int res = tsum(m);
        root = merge(l, merge(m, r));
        return res;
    }

    void add(int lx, int rx, T val) {
        auto [l, t] = split(root, lx);
        auto [m, r] = split(t, rx-lx+1);
        m->add += val;
        root = merge(l, merge(m, r));
    }

    void reverse(int lx, int rx) {
        auto [l, t] = split(root, lx);
        auto [m, r] = split(t, rx-lx+1);
        m->rev ^= 1;
        root = merge(l, merge(m, r));
    }
};

int main() {
    int n, temp;
    cin >> n;
    treap<int> t;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        t.pushBack(temp);
    }

    for (int i = 0; i < n; i++)
        cout << t.get(i) << " ";
    cout << "\n" << t.get(1, 3) << "\n";

    t.add(1, 3, 10);
    cout << t.get(1, 3) << "\n";
    t.reverse(1, 3);
    for (int i = 0; i < n; i++)
        cout << t.get(i) << " ";
}
