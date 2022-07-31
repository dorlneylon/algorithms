#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, prior;
    Node *l = 0, *r = 0;
    Node(int key) : key(key), prior(rand()) {}
    ~Node() {
        if (l != 0)
            delete l;
        if (r != 0)
            delete r;
    }
};

bool exists(Node* root, int x) {
    if (!root) return false;
    else if (root->key == x) return true;
    else if (root->key < x)
        return exists(root->r, x);
    else
        return exists(root->l, x);
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->prior > r->prior) {
        l->r = merge(l->r, r);
        return l;
    } else {
        r->l = merge(l, r->l);
        return r;
    }
}

pair<Node*, Node*> split(Node* p, int x) {
    if (!p) return {0,0};
    if (p->key <= x) {
        auto [l, r] = split(p->r, x);
        p->r = l;
        return {p,r};
    } else {
        auto [l, r] = split(p->l, x);
        p->l = r;
        return {l, p};
    }
}

Node* insert(Node* root, int x) {
    if (exists(root, x))
        return root;
    auto [l, r] = split(root, x);
    Node* t = new Node(x);
    root = merge(l, merge(t, r));
    return root;
}

Node* remove(Node* root, int x) {
    if (!exists(root, x))
        return root;
    auto [tmp, r] = split(root, x);
    auto [l, val] = split(tmp, x-1);
    delete val;
    return merge(l, r);
}

int main() {
    Node* root = 0;
    for (int i = 0; i < 200000; i+=2)
        root = insert(root, i);
    int c = 0;
    for (int i = 0; i < 200000; i++)
        if (exists(root, i)) c++;
    cout << c << "\n";
    for (int i = 0; i < 200000; i+=4)
        root = remove(root, i);
    c = 0;
    for (int i = 0; i < 200000; i++)
        if (exists(root, i)) c++;
    cout << c;
}