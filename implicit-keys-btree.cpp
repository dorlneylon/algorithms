#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *l = 0, *r = 0;
    int val, prior, size, minValue;
    Node(int val): val(val), prior(rand()), size(1), minValue(val) {}
    ~Node() {
        delete l;
        delete r;
    }
};

int getSize(Node *p) {
    return p ? p->size : 0;
}

int getminval(Node *p) {
    return p ? p->minValue : 1e9;
}

void upd(Node *p) {
    if (p) {
        p->size = getSize(p->l) + 1 + getSize(p->r);
        p->minValue = min(min(getminval(p->l), p->minValue), getminval(p->r));
    }
}

int size(Node *root) {
    return getSize(root);
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
    if (getSize(root->l) < x) {
        auto [l, r] = split(root->r, x - getSize(root->l) - 1);
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

int get(Node *root, int index) {
    auto [l, tmp] = split(root, index);
    auto [eq, g] = split(tmp, 1);
    int res = eq->val;
    root = merge(l, merge(eq, g));
    return res;
}

Node* pushBack(Node* root, int x) {
    root = merge(root, new Node(x));
    return root;
}

Node* pushFront(Node* root, int x) {
    root = merge(new Node(x), root);
    return root;
}

Node* push(Node *root, int ind, int val) {
    auto [l, g] = split(root, ind);
    return merge(l, merge(new Node(val), g));
}

Node* remove(Node *root, int x) {
    if (!get(root, x)) return root;
    auto [t, r] = split(root, x);
    auto [l, val] = split(t, 1);
    delete val;
    return merge(l, r);
}

Node* remove(Node* root, int lx, int rx) {
    auto [l, t1] = split(root, lx);
    auto [t2, r] = split(t1, rx-lx+1);
    return merge(l, r);
}

int findmin(Node *root, int lx, int rx) {
    auto [l, t] = split(root, lx);
    auto [eq, g] = split(t, rx-lx+1);
    int res = getminval(eq);
    root = merge(l, merge(eq, g));
    return res;
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

Node* revolve(Node *root, int lx, int rx, int t) {
    auto [l, tmp] = split(root, lx);
    auto [eq, r] = split(tmp, rx-lx+1);
    int n = getSize(eq);
    int ind = t%n;
    auto [l2, tmp3] = split(eq, n - ind);
    eq = merge(tmp3, l2);
    return merge(l, merge(eq, r));
}

int main () {
    Node *root = 0;

    root = pushBack(root, 1);
    root = pushBack(root, 2);
    root = pushBack(root, 3);
    root = pushBack(root, 4);
    root = pushBack(root, 5);

    for (int i = 0; i < size(root); i++)
        cout << get(root, i) << " ";

//    root = push(root, 2, 0);
//
//    for (int i = 0; i < size(root); i++)
//        cout << get(root, i) << " ";

    cout << "\n";

    root = revolve(root, 1, 3, 2);

    for (int i = 0; i < size(root); i++)
        cout << get(root, i) << " ";

    cout << "\n" << findmin(root, 1, 4);

}