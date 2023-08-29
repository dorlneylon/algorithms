#include <bits/stdc++.h>
#include "../Splay/splay.cpp"

template <typename node, int MAXSIZE = 500000,
          class alloc = allocator::array<node, MAXSIZE + 2>>
struct LinkCut : splay::tree<node, MAXSIZE, alloc> {
    virtual void expose(node *x) { // make x the root of the represented tree
        node *y = nullptr;
        for (node *z = x; z; z = z->f) {
            splay::splay(z);
            z->c[1] = y;
            z->update();
            y = z;
        }
        splay::splay(x);
    }

    virtual void link(node *x, node *y) { // make x a child of y
        expose(x);
        expose(y);
        x->f = y;
        y->c[1] = x;
        y->update();
    }

    virtual void cut(node *x) { // cut x from its parent
        expose(x);
        if (x->c[0]) {
            x->c[0]->f = nullptr;
            x->c[0] = nullptr;
            x->update();
        }
    }

    virtual node *root(node *x) { // find the root of the represented tree
        expose(x);
        while (x->c[0]) x = x->c[0];
        splay::splay(x);
        return x;
    }

    virtual void evert(node *x) { // make x the root of the reversed tree
        expose(x);
        x->reverse();
    }

    virtual node *lca(node *x, node *y) { // find the lowest common ancestor of x and y
        if (root(x) != root(y)) return nullptr;
        expose(x);
        return expose(y), x;
    }

    virtual void cut(node *x, node *y) { // cut the path from x to y
        evert(x);
        cut(y);
    }

    virtual void link(node *x, node *y, bool evert = false) { // link the path from x to y
        if (evert) this->evert(x);
        link(x, y);
    }
};