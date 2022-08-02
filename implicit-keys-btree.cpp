#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *l = 0, *r = 0;
    int prior, val, size, minvalue;
    bool rev;
    Node(int val): size(1), val(val), prior(rand()), minvalue(val), rev(0) {}
    ~Node() {
        delete l;
        delete r;
    }
};

struct Treap {
    Node *root = 0;

    int size() {
        return root->size;
    }

    int nodesize(Node *p) {
        return p ? p->size : 0;
    }

    int getSize(Node *root) {
        if (root) return nodesize(root->l) + 1 + nodesize(root->r);
        return 0;
    }

    long long getminval(Node *p) {
        return p ? p->minvalue : 1e9;
    }

    long long minimal(Node *p) {
        return min(getminval(p->l), min((long long)p->val, getminval(p->l)));
    }

    void push(Node *p) {
        if (p && p->rev) {
            p->rev = false;
            swap (p->l, p->r);
            if (p->l)
                p->l->rev ^= true;
            if (p->r)
                p->r->rev ^= true;
        }
    }

    void incr(Node *p, int val) {
        if (p) {
            p->val += val;
            incr(p->l, val);
            incr(p->r, val);
        }
    }

    void update(Node *p) {
        if (p) {
            p->size = getSize(p);
            p->minvalue = minimal(p);
        }
    }

    pair <Node*, Node*> split(Node *p, int ind) {
        if (!p) return {0,0};
        push(p);
        if (getSize(p->l) < ind) {
            auto [l, r] = split(p->r, ind - getSize(p->l) - 1);
            p->r = l;
            update(p);
            update(r);
            return {p, r};
        } else {
            auto [l, r] = split(p->l, ind);
            p->l = r;
            update(p);
            update(l);
            return {l, p};
        }
    }

    Node* merge(Node *l, Node *r) {
        push(l);
        push(r);
        if (!l) return r;
        if (!r) return l;
        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            update(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            update(r);
            return r;
        }
    }

    void insert(int x, int ind) {
        auto [l, t] = split(root, ind);
        root = merge(l, merge(new Node(x), t));
    }

    void pushBack(int x) {
        root = merge(root, new Node(x));
    }

    void pushFront(int x) {
        root = merge(new Node(x), root);
    }

    int get(int ind) {
        auto [l, t] = split(root, ind);
        auto [val, g] = split(t, 1);
        int res = val->val;
        root = merge(l, merge(val, g));
        return res;
    }

    void remove(int x) {
        auto [l, t] = split(root, x);
        auto [val, r] = split(root, 1);
        delete val;
        root = merge(l, r);
    }

    void increment(int lx, int rx, int val) {
        auto [l, t] = split(root, lx);
        auto [m, r] = split(t, rx-lx+1);
        incr(m, val);
        root = merge(l, merge(m, r));
    }

    long long minValue(int lx, int rx) {
        auto [l, t] = split(root, lx);
        auto [m, r] = split(t, rx-lx+1);
        auto k = minimal(m);
        root = merge(l, merge(m, r));
        return k;
    }

    void reverse(int lx, int rx) {
        auto [l, t] = split(root, lx);
        auto [m, r] = split(root, rx-lx+1);
        m->rev ^= true;
        root = merge(l, merge(m, r));
    }

};

int main() {
    Treap t;
    int k;
    cin >> k;

    for (int i = 0; i < k; i++) {
        int temp;
        cin >> temp;
        t.pushBack(temp);
    }
}