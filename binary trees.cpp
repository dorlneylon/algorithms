#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *l = 0, *r = 0;
    int val, prior, size;
    long long s;
    Node(int val): val(val), prior(rand()), size(1), s(val) {}
    ~Node() {
        delete l;
        delete r;
    }
};

long long getSum(Node *p) {
    return p ? p->s : 0;
}

void updateSum(Node *p) {
    if (p) p->s = getSum(p->l) + p->val + getSum(p->r);
}

int getSize(Node *p) {
    return p ? p->size : 0;
}

void updateSize(Node *p) {
    if (p) p->size = getSize(p->l) + 1 + getSize(p->r);
}

void upd(Node *p) {
    updateSize(p);
    updateSum(p);
}

bool exists(Node *root, int x) {
    if (!root) return false;
    if (root->val == x) return true;
    if (root->val <= x)
        exists(root->r, x);
    else
        exists(root->l, x);
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
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

// Как это блядь работает?
pair <Node*, Node*> split(Node *root, int x) {
    if (!root) return {0,0};
    if (root->val <= x) {
        auto [l, r] = split(root->r, x);
        root->r = l;
        upd(root);
        upd(r);
        return {root, r};
    } else {
        auto [l, r] = split(root->l, x);
        root->l = r;
        upd(root);
        upd(l);
        return {l, root};
    }
}

Node* insert(Node* root, int x) {
    if (exists(root, x)) return root;
    auto [l, r] = split(root, x);
    Node *p = new Node(x);
    return merge(l, merge(p, r));
}

Node* remove(Node *root, int x) {
    if (!exists(root, x)) return root;
    auto [t, r] = split(root, x);
    auto [l, val] = split(t, x-1);
    delete val;
    return merge(l, r);
}

int IndexByVal(Node *root, int key) {
    auto [l, g] = split(root, key-1);
    int res = getSize(l);
    root = merge(l,g);
    return res;
}

int ValByIndex(Node *p, int ind) {
    int ls = getSize(p->l);
    if (ind == ls) return p->val;
    else if (ind < ls) return ValByIndex(p->l, ind);
    else return ValByIndex(p->r, ind - ls - 1);
}

long long sum(Node *root, int l, int r) {
    auto [less, tmp] = split(root, l-1);
    auto [eq, greater] = split(tmp, r);
    long long res = getSum(eq);
    root = merge(less, merge(eq, greater));
    return res;
}

int main () {
    Node *root = 0;
    root = insert(root, 23);
    root = insert(root, 55);
    root = insert(root, 14);
    root = insert(root, 67);
    root = insert(root, 46);
    // 14 23 46 55 67

    cout << IndexByVal(root, 14) << " " << IndexByVal(root,23) << " " << IndexByVal(root, 46) << " " << IndexByVal(root, 55) << " "<< IndexByVal(root, 67) << "\n";
    cout << ValByIndex(root, 0) << " " << ValByIndex(root, 1) << " " << ValByIndex(root, 2) << " " << ValByIndex(root, 3) << " " << ValByIndex(root, 4);
    cout << "\n";

    root = remove(root, 23);
    root = remove(root, 55);
    root = remove(root, 14);
    root = remove(root, 67);
    root = remove(root, 46);

    root = insert(root, 5);
    root = insert(root, 9);
    root = insert(root, 7);
    root = insert(root, 2);

    cout << sum(root, 5, 10) << "\n";
    root = remove(root, 7);
    cout << sum(root, 5, 10);
}