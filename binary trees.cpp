#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    int data;

    Node(int d) {
        left = 0;
        right = 0;
        data = d;
    }
};

class BinaryTree {
private:
    Node* root = 0;
    int __size = 0;

    bool inner_find(int t, Node* current) {
        if (current == 0)
            return false;
        else if (current->data == t)
            return true;
        else if (current->data > t)
            return inner_find(t, current->left);
        else
            return inner_find(t, current->right);
    }

    Node* inner_insert(int t, Node* current) {
        if (current == 0) {
            __size++;
            return new Node(t);
        }
        else if (current->data > t)
            current->left = inner_insert(t, current->left);
        else if (current->data < t)
            current->right = inner_insert(t, current->right);
        return current;
    }

    void inner_traversal(Node* current, vector<int> &elements) {
        if (current == 0)
            return;
        inner_traversal(current->left, elements);
        elements.push_back(current->data);
        inner_traversal(current->right, elements);
    }

    Node* inner_remove(int t, Node* current) {
        if (current == 0)
            return 0;
        if (t < current->data)
            current->left = inner_remove(t, current->left);
        else if (t > current->data)
            current->right = inner_remove(t, current->right);
        else {
            if (current->left == 0 && current->right == 0) {
                delete current;
                return 0;
            } else if (current->left != 0 && current->right == 0) {
                Node* tmp = current->left;
                delete current;
                return tmp;
            } else if (current->left == 0 && current->right != 0) {
                Node* tmp = current->right;
                delete current;
                return tmp;
            } else {
                int d = inner_min(current->right);
                current->data = d;
                current->right = inner_remove(d, current->right);
            }
        }
        return current;
    }

    int inner_min(Node* current) {
        if (__size == 0)
            return 1e9;
        Node* tmp = current;
        while (tmp->left) {
            tmp = tmp->left;
        }
        return tmp->data;
    }

    int inner_max(Node* current) {
        if (__size == 0)
            return -1e9;

        Node* tmp = current;
        while (tmp->right) {
            tmp = tmp->right;
        }
        return tmp->data;
    }
public:
    BinaryTree() {
    }

    bool find(int t) {
        return inner_find(t, root);
    }

    void insert(int t) {
        root = inner_insert(t, root);
    }

    int size() {
        return __size;
    }

    vector<int> get_elements() {
        vector<int> elements;
        inner_traversal(root, elements);
        return elements;
    }

    int maximum() {
        return inner_max(root);
    }

    int minimum() {
        return inner_min(root);
    }

    void remove(int t) {
        inner_remove(t, root);
    }
};

int main () {
    int n;
    cin >> n;
    BinaryTree bt;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        bt.insert(t);
    }
    vector<int> elems = bt.get_elements();
    for (int i = 0; i < elems.size(); i++) {
         cout << elems[i] << " ";
    }
    cout << "\n";
    bt.remove(4);
    elems = bt.get_elements();
    for (int i = 0; i < elems.size(); i++) {
        cout << elems[i] << " ";
    }
}