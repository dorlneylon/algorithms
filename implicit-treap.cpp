#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *l = nullptr, *r = nullptr;
    int val, prior, mn, size, add = 0, s;
    bool rev = false;
    Node(int val): val(val), prior(rand()), mn(val), size(1), s(val) {}
    ~Node() {
        delete l;
        delete r;
    }
};

struct Treap {
    Node *root = nullptr;

    int ts(Node *p) {
        return p ? p->size : 0;
    }

    int tm(Node *p) {
        return p ? p->mn + p->add : 1e9;
    }

    int tsum(Node *p) {
        return p ? p->s + p->add : 0;
    }

    int gs(Node *p) {
        return p ? ts(p->l) + ts(p->r) + 1 : 0;
    }

    void push(Node *p) {
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

    void upd(Node *p) {
        if (!p) return;
        p->size = ts(p->l) + ts(p->r) + 1;
        p->mn = min(tm(p->l), min(tm(p->r), p->val + p->add));
        p->s = tsum(p->l) + p->val + tsum(p->r) + p->add;
    }

    pair<Node*, Node*> split(Node *p, int k) {
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

    Node* merge(Node *l, Node *r) {
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

    void pushBack(int val) {
        root = merge(root, new Node(val));
    }

    int mnval(int lx, int rx) {
        auto [l, t] = split(root, lx);
        auto [m, r] = split(t, rx-lx+1);
        int res = m->mn;
        root = merge(l, merge(m, r));
        return res;
    }

    int get(int k) {
        auto [l, t] = split(root, k);
        auto [node, r] = split(t, 1);
        int res = node->val;
        root = merge(l, merge(node, r));
        return res;
    }

    int get(int lx, int rx) {
        auto [l, t] = split(root, lx);
        auto [m, r] = split(t, rx-lx+1);
        int res = tsum(m);
        root = merge(l, merge(m, r));
        return res;
    }

    void add(int lx, int rx, int val) {
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
    Treap t;
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